#include <ArduinoJson.h>
#include <Arduino.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>
#include <SPI.h>
#include <Preferences.h>
#include <HTTPClient.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#include <DNSServer.h>
//potentially important for screen: https://www.youtube.com/watch?v=WHl2oC8fqZU
#include "SSD1306Wire.h" // legacy include: `#include "SSD1306.h"`
#include "OLEDDisplayUi.h"
//#include "images.h"

//Check for TODO

//254985 Public drafted league

//Active Players check if played via "lockstatus" 0 is not yet 4 is it's over? search for lockstatus in json viewer. Players from 0-7 are starting, only check those

Preferences preferences;
IPAddress apIP(192, 168, 1, 1);
DNSServer dnsServer;
WebServer webServer(80);

const char *APssid = "FFL";

String getSSID;
String getSSIDPW;
String getLeagueID;
String getTeamID;
String getSeasonID;
int getStarters;
String getUsername;
String getESPNPW;

const String URLBase = "http://games.espn.com/ffl/api/v2/boxscore";
const String LeagueID = "?leagueId=";
const String SeasonID = "&seasonId=";
const String TeamID = "&teamId=";
bool isError = false;
bool variablesInitialized = false;

const char * teamAbbrevHome;
const char * teamAbbrevAway;
const char * teamScoreHome;
const char * teamScoreAway;
const char * week;
int remainingHome; //matchupPeriodId is "game", scoreingPeriodId is actuall NFL week, so playoff multi week fantasy games differ in these two
int remainingAway;


String * htmlIndex;
extern String htmlAP;
extern String htmlConnected;
extern void createHTML();

String errorMessage;

void setup() {
  Serial.begin(115200);

  //xTaskCreate(printToScreen, "LCD", 4096, NULL , 1, NULL);

  preferences.begin("towerlight", false);
  initStaticVariables();
  createHTML();

  WiFi.begin(getSSID.c_str(), getSSIDPW.c_str());
  Serial.println("Trying to Connect to WIFI");
  for (int i = 0; i < 25; i++) {
    if (WiFi.status() != WL_CONNECTED) {
      Serial.print(".");
      delay(250);
    }
    else {
      Serial.println("");
      break;
    }
  }

  if (WiFi.status() != WL_CONNECTED) {
    htmlIndex = &htmlAP;
    WiFi.mode(WIFI_AP);
    WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
    WiFi.softAP(APssid);
    Serial.println("\nAccess Point started");
    Serial.println(WiFi.softAPIP());
    dnsServer.start(53, "*", WiFi.softAPIP());
  } else {
    htmlIndex = &htmlConnected;
    Serial.println("WIFI Connection established");
    IPAddress ip = WiFi.localIP();
    Serial.print("IP Address: ");
    Serial.println(ip);
  }

  webServer.on("/", handleSaveRequest);
  webServer.onNotFound(handleSaveRequest);

  webServer.begin();
  Serial.println("HTTP server started");

  ArduinoOTA.onStart([]() {
    String type;
    if (ArduinoOTA.getCommand() == U_FLASH)
      type = "sketch";
    else // U_SPIFFS
      type = "filesystem";
    Serial.println("Start updating " + type);
  });
  ArduinoOTA.onEnd([]() {
    Serial.println("\nEnd");
  });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
  });
  ArduinoOTA.onError([](ota_error_t error) {
    Serial.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR)         Serial.println("Auth Failed");
    else if (error == OTA_BEGIN_ERROR)   Serial.println("Begin Failed");
    else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
    else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
    else if (error == OTA_END_ERROR)     Serial.println("End Failed");
  });
  ArduinoOTA.begin();
  Serial.println("OTA Enabled");

}

void debugError(int httpCode) {
  if (httpCode == 401) {
    Serial.println("401 - Authentication Error!");
    errorMessage = "401 - Authentication Error!";
  }
  else if (httpCode == 404) {
    Serial.println("404 - Not Found");
    errorMessage = "404 - Not Found";
  }
  else if (httpCode == -1) {
    Serial.println("'-1' - HTTPC_ERROR_CONNECTION_REFUSED");
    errorMessage = "'-1' - HTTPC_ERROR_CONNECTION_REFUSED";
  }
  else if ((WiFi.status() != WL_CONNECTED)) {
    Serial.println("'999' No Connection to the Internet");
    errorMessage = "'999' No Connection to the Internet";
  }
}

void requestLogic() {
  bool allRequestsWorked = true;
  String requestUrl = URLBase + LeagueID + String() + TeamID + String() + SeasonID + String();
  if (variablesInitialized && (WiFi.status() == WL_CONNECTED)) {
    HTTPClient http;
    http.setAuthorization(getUsername.c_str(), getESPNPW.c_str());
    http.begin(requestUrl);
    int httpCode = http.GET();
    debugError(httpCode);
    if (httpCode == HTTP_CODE_OK) {
      doJSON(http.getString());
    } else {
      allRequestsWorked = false;
    }
    http.end();
  }
  if (isError) {
    printErrorToScreen();
  }
  if (allRequestsWorked) {
    printToScreen();
  }
}

void handleIndex() {
  webServer.send(200, "text/html", htmlIndex->c_str());
}

void doJSON(String json)
{
  const size_t bufferSize = 37 * JSON_ARRAY_SIZE(1) + 8 * JSON_ARRAY_SIZE(2) + 25 * JSON_ARRAY_SIZE(3) + 2 * JSON_ARRAY_SIZE(16) + 36 * JSON_OBJECT_SIZE(0) + 13 * JSON_OBJECT_SIZE(1) + 14 * JSON_OBJECT_SIZE(2) + 40 * JSON_OBJECT_SIZE(3) + JSON_OBJECT_SIZE(5) + JSON_OBJECT_SIZE(6) + 4 * JSON_OBJECT_SIZE(7) + 4 * JSON_OBJECT_SIZE(8) + 17 * JSON_OBJECT_SIZE(9) + JSON_OBJECT_SIZE(10) + 18 * JSON_OBJECT_SIZE(11) + 17 * JSON_OBJECT_SIZE(12) + 4 * JSON_OBJECT_SIZE(13) + 2 * JSON_OBJECT_SIZE(14) + 2 * JSON_OBJECT_SIZE(15) + 2 * JSON_OBJECT_SIZE(16) + 2 * JSON_OBJECT_SIZE(17) + 2 * JSON_OBJECT_SIZE(18) + 3 * JSON_OBJECT_SIZE(19) + 2 * JSON_OBJECT_SIZE(20) + 2 * JSON_OBJECT_SIZE(21) + JSON_OBJECT_SIZE(22) + 3 * JSON_OBJECT_SIZE(24) + 29 * JSON_OBJECT_SIZE(25) + JSON_OBJECT_SIZE(26) + 2 * JSON_OBJECT_SIZE(27) + JSON_OBJECT_SIZE(33) + 34190;
  DynamicJsonBuffer jsonBuffer(bufferSize);
  JsonObject& root = jsonBuffer.parseObject(json);
  //https://codebeautify.org/jsonviewer
  //https://arduinojson.org/v5/assistant/

  JsonObject& metadata = root["metadata"];
  JsonObject& boxscore = root["boxscore"];
  JsonObject& teamAway = boxscore["teams"][0];
  JsonObject& teamHome = boxscore["teams"][1];
  remainingAway = 0;
  remainingHome = 0;
  for (int i = 0; i < getStarters; i++) { //TODO -ASCII CODE
    if (teamAway["slots"][i]["lockstatus"] == 0)
      remainingAway++;
  }
  for (int i = 0; i < getStarters; i++) { //TODO -ASCII CODE
    if (teamHome["slots"][i]["lockstatus"] == 0)
      remainingHome++;
  }

  teamAbbrevHome = teamHome["team"]["teamAbbrev"];//boxscore/teams/0/team/teamabrev
  teamAbbrevAway = teamAway["team"]["teamAbbrev"];
  teamScoreHome = teamHome["appliedActiveRealTotal"];//boxscore/teams/0/appliedActiveRealTotal
  teamScoreAway = teamAway["appliedActiveRealTotal"];
  week = boxscore["scheduleItems"][0]["matchupPeriodId"];
  //String payload = http.getString();
}

void initStaticVariables() {
  getSSID = preferences.getString("getSSID");
  getSSIDPW = preferences.getString("getSSIDPW");
  getLeagueID = preferences.getString("getLeagueID");
  getTeamID = preferences.getString("getTeamID");
  getSeasonID = preferences.getString("getSeasonID");
  getStarters = preferences.getInt("getStarters");
  getUsername = preferences.getString("getUsername");
  getESPNPW = preferences.getString("getESPNPW");
  if (getSSID == "" || getSSIDPW == "" || getLeagueID == "" || getUsername == "" || getESPNPW == "")
    variablesInitialized = false;
  else
    variablesInitialized = true;
}

void handleSaveRequest() {
  bool restart = false;
  if (webServer.hasArg("ssid_input")) {
    if ((webServer.arg("ssid_input") != "") || (webServer.arg("wifipw_input") != "")) {
      if ((webServer.arg("ssid_input") != preferences.getString("getSSID")) || (webServer.arg("wifipw_input") != preferences.getString("getSSIDPW"))) {
        restart = true; //Restart required if SSID or PW has changed
        Serial.println("restart scheduled!");
      }
    }

    preferences.putString("getSSID", webServer.arg("ssid_input"));
    preferences.putString("getSSIDPW", webServer.arg("wifipw_input"));
    preferences.putString("getLeagueID", webServer.arg("leagueid_input"));
    preferences.putString("getTeamID", webServer.arg("teamid_input"));
    preferences.putString("getSeasonID", webServer.arg("seasonid_input"));
    preferences.putInt("getStarters", webServer.arg("starters_input").toInt()); //TODO Check if to int onverts "123" to 123 instead of ASCII stufff
    preferences.putString("getUsername", webServer.arg("espnusername_input"));
    preferences.putString("getESPNPW", webServer.arg("espnpw_input"));

    initStaticVariables();

    createHTML();
  }

  handleIndex();

  if (restart)
    ESP.restart();
}

void printErrorToScreen() {
  Serial.println("ERROR!!!!!");
  Serial.println(errorMessage);
}

void printToScreen() { //https://www.arduino.cc/en/Reference/LiquidCrystal
  Serial.println("Week: ");
  Serial.print(week);

  Serial.println(teamAbbrevAway);
  Serial.print(": ");
  Serial.print(teamScoreAway);
  Serial.print(" Remaining: ");
  Serial.print(remainingAway);

  Serial.println(teamAbbrevHome);
  Serial.print(": ");
  Serial.print(teamScoreHome);
  Serial.print(" Remaining: ");
  Serial.print(remainingHome);
}

void loop() {
  dnsServer.processNextRequest();
  ArduinoOTA.handle();
  yield();
  webServer.handleClient();
  requestLogic();
  delay(500);
}

