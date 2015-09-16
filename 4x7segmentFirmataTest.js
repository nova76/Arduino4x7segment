function lpad(n, width, z) {
  z = z || '0';
  n = n + '';
  return n.length >= width ? n : new Array(width - n.length + 1).join(z) + n;
}

// node install firmata :-)
var firmata = require('firmata');
console.log(1);
var board = new firmata.Board('COM3', function(err) { // COM5: Arduino comm. port
  console.log('connected!');
  console.log('Firmware: ' + board.firmware.name + '-' + board.firmware.version.major + '.' + board.firmware.version.minor);

  board.on('string', function(string){
    console.log('receiving string: "%s"', string);
  });

  board.sendString("DISPLAY|ON")	

  lights = '0000';	
  
  setInterval(function() {
	board.sendString("DISPLAY|"+lights)	
	lights = lpad(parseInt(lights) + 1, 4, '0')
  }, 1000);
});


