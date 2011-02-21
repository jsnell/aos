<html>
  <head>
    <title>Age of Steam</title>
    <script type="text/javascript" language="javascript"
                  src="/home/jsnell/prog/omat/aos/js/prototype-1.6.0.3.js">
    </script>
    <script type="text/javascript" language="javascript"
            src="/home/jsnell/prog/omat/aos/js/game.js">
    </script>
  </head>
  <body>
    <style type="text/css">
      div.player {
          border-style: solid;
          margin: 2px;
          padding: 3px;
          width: 200px;
          float: left;
      }
      table { border-style: solid }
      table { border-style: solid }

      div.color-red { background-color: #e04040 }
      div.color-green { background-color: #40a040 }
      div.color-yellow { background-color: #e0e040 }
      div.color-blue { background-color: #4040e0 }
      div.color-black { background-color: #000000 }
      div.color-purple { background-color: #990099 }
      
      div#turn-order { display: none }
      canvas#map { border-style: solid }
    </style>

    <div id="players">
      {{#PLAYER}}
      <div class="player"
           {{#ACTIVE}}style="background-color: #d0d0d0"{{/ACTIVE}}>
        <div class="color-{{COLOR}}" style="color: white; padding: 3px">
          {{NAME}}
        </div>
        ${{CASH}} cash, {{LOANS}} loans, link level {{LINK_LEVEL}}<br>
        {{POWER}}
      </div>
      {{/PLAYER}}
    </div>
    <div id="map-container">
      <canvas id="map" width="1024" height="680">
        Browser not supported.
      </canvas>
    </div>
    <script language="javascript">
      var state = {
        "map": [
          {{#HEX}}
          { row: '{{ROW}}', col: '{{COL}}', terrain: '{{TERRAIN}}',
            tracks: [{{#TRACK}}{from:[{{FROM_ROW}}, {{FROM_COL}}], to:[{{TO_ROW}}, {{TO_COL}}], color:'{{COLOR}}' }, {{/TRACK}}],
            {{#CITY}}city: { color: '{{COLOR}}' }, {{/CITY}}
          },
          {{/HEX}}
        ]
      }
      DrawMap();
    </script>
    <div id="turn-order">
      <table class="turn-order">
        <tr>
          {{#ORDER}}
          <td class="active-{{ACTIVE}}">
            <div class="color-{{COLOR}}">{{COLOR}}</div>
          </td>
          {{/ORDER}}
        </tr>
      </table>
    </div>
    <pre>{{OPTIONS}}</pre>
  </body>
</html>
