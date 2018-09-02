extern String getSSID;
extern String getSSIDPW;
extern String getLeagueID;
extern String getTeamID;
extern String getSeasonID;
extern String getUsername;
extern String getESPNPW;
String htmlConnected = "";
String htmlAP = "";
void createHTML(){
  
String htmlAP ="<!DOCTYPE html>\
<html>\
\
<head>\
  <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\
  <style>\
    html,\
    body {\
      background-color: #dddddd;\
    }\
\
    input[type=submit] {\
      background-color: #db2000;\
      color: white;\
      padding: 12px 20px;\
      border: none;\
      border-radius: 4px;\
      cursor: pointer;\
      margin-top: 6px;\
      position: relative;\
    }\
\
    input[type=submit]:hover {\
      background-color: #45a049;\
    }\
\
    .container {\
      margin-top: 25px;\
      width: 100%;\
      border-radius: 5px;\
      background-color: #dddddd;\
      position: absolute;\
      top: 15%;\
      left: 50%;\
      transform: translate(-50%);\
    }\
\
    input[type=text],\
    select,\
    textarea {\
      padding: 12px;\
      border: 1px solid #ccc;\
      border-radius: 4px;\
      background-color: white;\
      color: #777777;\
      resize: vertical;\
      width: 100% !important;\
      box-sizing: border-box;\
      display: block;\
    }\
\
    label {\
      padding-top: 15px;\
      padding-left: 5px;\
      padding-bottom: : 2px;\
      float: left;\
      font-family: \"Arial\", Arial, sans;\
      color: #333333;\
    }\
\
    .header {\
      color: #db2000;\
      font-family: \"Arial\", Arial, sans;\
      position: relative;\
      font-size: 250%;\
      font-weight: bold;\
    }\
\
    .row {\
      display: table;\
      margin: 0 auto;\
      width: 75%;\
    }\
\
    .button {\
      display: table;\
      margin: 0 auto;\
    }\
\
    @media (min-width: 850px) {\
      .container {\
        margin-top: 0px;\
        width: 40%;\
        top: 50%;\
        transform: translate(-50%, -50%);\
        padding: 20px;\
      }\
\
      .header {\
        font-size: 5em;\
      }\
\
      html,\
      body {\
        background-color: #111111;\
      }\
    }\
  </style>\
</head>\
\
<body>\
  <div class=\"container\">\
    <center>\
      <h class=\"header\">ESPN32</h>\
    </center>\
    <form>\
      <div class=\"row\">\
        <label for=\"ssid\">SSID</label> </br>\
        <input type=\"text\" id=\"ssid\" name=\"ssid_input\" placeholder=\"";
htmlAP += getSSID;
htmlAP +="\">\
      </div>\
      <div class=\"row\">\
        <label for=\"wifipw\">WIFI Password</label> </br>\
        <input type=\"text\" id=\"wifipw\" name=\"wifipw_input\" placeholder=\"";
htmlAP += getSSIDPW;
htmlAP +="\">\
      </div>\
      <div class=\"button\">\
        </br>\
        <input type=\"submit\" value=\"Submit\">\
      </div>\
    </form>\
  </div>\
</body>";


htmlConnected ="<!DOCTYPE html>\
<html>\
\
<head>\
  <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\
  <style>\
    html,\
    body {\
      background-color: #dddddd;\
    }\
\
    input[type=submit] {\
      background-color: #db2000;\
      color: white;\
      padding: 12px 20px;\
      border: none;\
      border-radius: 4px;\
      cursor: pointer;\
      margin-top: 6px;\
      position: relative;\
    }\
\
    input[type=submit]:hover {\
      background-color: #45a049;\
    }\
\
    .container {\
      margin-top: 25px;\
      width: 100%;\
      border-radius: 5px;\
      background-color: #dddddd;\
      position: absolute;\
      left: 50%;\
      transform: translate(-50%);\
      margin-bottom: 25px;\
    }\
\
    input[type=text],\
    select,\
    textarea {\
      padding: 12px;\
      border: 1px solid #ccc;\
      border-radius: 4px;\
      background-color: white;\
      color: #777777;\
      resize: vertical;\
      width: 100% !important;\
      box-sizing: border-box;\
      display: block;\
    }\
\
    label {\
      padding-top: 15px;\
      padding-left: 5px;\
      padding-bottom: : 2px;\
      float: left;\
      font-family: \"Arial\", Arial, sans;\
      color: #333333;\
    }\
\
    .header {\
      color: #db2000;\
      font-family: \"Arial\", Arial, sans;\
      position: relative;\
      font-size: 250%;\
      font-weight: bold;\
    }\
\
    .row {\
      display: table;\
      margin: 0 auto;\
      width: 75%;\
    }\
\
    .button {\
      display: table;\
      margin: 0 auto;\
    }\
    @media (min-width: 800px) {\
      .container {\
        margin-top: 0px;\
        width: 50%;\
        top: 20px;\
        transform: translate(-50%);\
        margin-bottom: 100px;\
        padding: 20px;\
      }\
\
      .header {\
        font-size: 500%;\
      }\
\
      html,\
      body {\
        background-color: #111111;\
      }\
    }\
  </style>\
</head>\
\
<body>\
  <div class=\"container\">\
    <center>\
      <h class=\"header\">ESPN32</h>\
    </center>\
    <form>\
      <div class=\"row\">\
        <label for=\"ssid\">SSID</label> </br>\
        <input type=\"text\" id=\"ssid\" name=\"ssid_input\" placeholder=\"";
htmlConnected += getSSID;
htmlConnected +="\">\
      </div>\
      <div class=\"row\">\
        <label for=\"wifipw\">WIFI Password</label> </br>\
        <input type=\"text\" id=\"wifipw\" name=\"wifipw_input\" placeholder=\"";
htmlConnected += getSSIDPW;
htmlConnected +="\">\
      </div>\
      <div class=\"row\">\
        <label for=\"leagueid\">League ID</label> </br>\
        <input type=\"text\" id=\"leagueid\" name=\"leagueid_input\" placeholder=\"";
htmlConnected += getLeagueID;
htmlConnected +="\">\
      </div>\
      <div class=\"row\">\
        <label for=\"teamid\">Team ID</label> </br>\
        <input type=\"text\" id=\"teamid\" name=\"teamid_input\" placeholder=\"";
htmlConnected += getTeamID;
htmlConnected +="\">\
      </div>\
      <div class=\"row\">\
        <label for=\"seasonid\">Season</label> </br>\
        <input type=\"text\" id=\"seasonid\" name=\"seasonid_input\" placeholder=\"";
htmlConnected += getSeasonID;
htmlConnected +="\">\
      </div>\
      <div class=\"row\">\
        <label for=\"espnusername\">Pipeline Username</label> </br>\
        <input type=\"text\" id=\"espnusername\" name=\"espnusername_input\" placeholder=\"";
htmlConnected += getUsername;
htmlConnected +="\">\
      </div>\
      <div class=\"row\">\
        <label for=\"espnpw\">Pipeline Password</label> </br>\
        <input type=\"text\" id=\"espnpw\" name=\"espnpw_input\" placeholder=\"";
htmlConnected += getESPNPW;
htmlConnected +="\">\
      </div>\
      <div class=\"button\">\
        </br>\
        <input type=\"submit\" value=\"Submit\">\
      </div>\
    </form>\
  </div>\
</body>";


}

