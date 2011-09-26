var game = null;
var state = null;

var hex_size = 35;
var hex_width = (Math.cos(Math.PI / 6) * hex_size * 2);
var hex_height = Math.sin(Math.PI / 6) * hex_size + hex_size;
var selected = {};

function HexCenter(row, col) {
    var x_offset = row % 2 ? hex_width / 2 : 0;
    var x = 5 + hex_size + col * hex_width + x_offset,
        y = 5 + hex_size + row * hex_height;
    return [x, y];
}

var colors = {
    red: '#e04040',
    green: '#40a040',
    yellow: '#e0e040',
    blue: '#4040e0',
    black: '#000000',
    purple: '#990099',
    none: '#aaaaaa',
    white: '#ffffff',
};

function MakeHexPath(ctx, hex) {
    var loc = HexCenter(hex.row, hex.col);
    var x = loc[0] - Math.cos(Math.PI / 6) * hex_size;
    var y = loc[1] + Math.sin(Math.PI / 6) * hex_size;
    var angle = 0;
    
    ctx.beginPath();
    ctx.moveTo(x, y);
    for (var i = 0; i < 6; i++) {
        ctx.lineTo(x, y); 
        angle += Math.PI / 3;
        x += Math.sin(angle) * hex_size;
        y += Math.cos(angle) * hex_size;        
    }
    ctx.closePath();
}

function MidPoint(a, b) {
    return [ (a[0] + b[0])/2,
             (a[1] + b[1])/2 ];
}

function DrawTrack(ctx, hex, from, to, color) {
    var loc = HexCenter(hex.row, hex.col);
    var from_loc = MidPoint(loc, HexCenter(from[0], from[1]));
    var to_loc = MidPoint(loc, HexCenter(to[0], to[1]));

    ctx.save();

    ctx.beginPath();
    ctx.moveTo(from_loc[0], from_loc[1]);
    ctx.quadraticCurveTo(loc[0], loc[1], to_loc[0], to_loc[1])
    ctx.strokeStyle = "#000000";
    ctx.lineWidth = 8;
    ctx.stroke();

    ctx.strokeStyle = colors[color];
    ctx.lineWidth = 5;
    ctx.stroke();

    ctx.restore();
}

function DrawCity(ctx, hex) {
    var loc = HexCenter(hex.row, hex.col);

    ctx.save();

    ctx.beginPath();
    ctx.arc(loc[0], loc[1], 24, 0, Math.PI*2);
    ctx.fillStyle = colors[hex.city.color];
    ctx.fill();

    ctx.restore();
}

function DrawTown(ctx, hex) {
    var loc = HexCenter(hex.row, hex.col);

    ctx.save();

    ctx.beginPath();
    ctx.arc(loc[0], loc[1], 14, 0, Math.PI*2);
    ctx.fillStyle = colors.white;
    ctx.fill();
    ctx.strokeStyle = "#000000";
    ctx.lineWidth = 1;
    ctx.stroke();

    ctx.restore();
}

function DrawHex(ctx, n) {
    var hex = state['map'][n];

    if (hex == null) {
        return;
    }

    MakeHexPath(ctx, hex);

    ctx.save();
    switch (hex.terrain & 7) {
    case 0:
        ctx.fillStyle = "#a0d0a0";
        break;
    case 1:
        ctx.fillStyle = "#ffffa0";
        break;
    case 2:
        ctx.fillStyle = "#808060";
        break;
    case 3:
        ctx.fillStyle = "#008000";
        break;
    }
    if (selected[n]) {
        ctx.fillStyle = "#ff00ff";
    }
    ctx.fill();
    ctx.restore();

    ctx.save();
    ctx.clip();
    hex.tracks.each(function (track, index) {
            DrawTrack(ctx, hex, track.from, track.to, track.color);
        });
    ctx.restore();

    ctx.save();
    ctx.strokeStyle = "#000000";
    ctx.lineWidth = 2;
    MakeHexPath(ctx, hex);
    ctx.stroke();
    ctx.restore();

    if (hex.city) {
        DrawCity(ctx, hex);
    }
    if (hex.town) {
        DrawTown(ctx, hex);
    }
}

function DrawMap() {
    var canvas = $("map");
    if (canvas.getContext) {
        var ctx = canvas.getContext("2d");
            
        state['map'].each(function(hex, index) { DrawHex(ctx, index) });
    }
}

function ClickLocation(e) {
    if (e.offsetX) {
        return [e.offsetX, e.offsetY];
    }

    var x = e.pageX, y = e.pageY;
    var obj = e.target;
    x -= obj.offsetLeft;
    y -= obj.offsetTop;
    return [x, y]
}

function ClickMap(e) {
    var loc = ClickLocation(e), x = loc[0], y = loc[1];

    var best_n = 0;
    var best_dist = null;
    for (n in map_info) {
        var dist =
            Math.pow(map_info[n].x - x, 2) +
            Math.pow(map_info[n].y - y, 2);
        if (best_dist == null || dist < best_dist) {
            best_dist = dist;
            best_n = n;
        }
    }

    selected[best_n] = !(selected[best_n] == true);

    var canvas = $("map");
    DrawHex(canvas.getContext("2d"), best_n);
}
