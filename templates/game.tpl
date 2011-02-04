<html>
  <head>
    <title>Age of Steam</title>
  </head>
  <body>
    <div id="players">
      {{#PLAYER}}
      <div class="player">
        <b class="color-{{COLOR}}">{{NAME}}</b><br>
        ${{CASH}} cash, {{LOANS}} loans, link level {{LINK_LEVEL}}<br>
        {{POWER}}
      </div>
      {{/PLAYER}}
    </div>
    <div id="turn-order">
      <table class="turn-order">
        <tr>
          {{#ORDER}}
          <td class="active-{{ACTIVE}}">
            {{COLOR}}
          </td>
          {{/ORDER}}
        </tr>
      </table>
    </div>
    <pre>{{OPTIONS}}</pre>
  </body>
</html>
