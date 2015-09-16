// http://ecotronics.ch.honorius.sui-inter.net/wordpress/2013/multiplexed-4-digit-7-segment-led-display-mit-arduino-ansteuern/
// http://learn.parallax.com/4-digit-7-segment-led-display-arduino-demo

var five = require("johnny-five");
var  DigitPins  = [10, 11,12,13];
var SegmentPins = [2, 3, 4, 5, 6, 7, 8, 9];

var matrix =[[ 1,1,1,1,1,1,0,0],
			[ 0,1,1,0,0,0,0,0],
			[ 1,1,0,1,1,0,1,0 ],
			[ 1,1,1,1,0,0,1,0 ],
			[ 0,1,1,0,0,1,1,0 ],
			[ 1,0,1,1,0,1,1,0 ],
			[ 1,0,1,1,1,1,1,0 ],
			[ 1,1,1,0,0,0,0,0 ],
			[ 1,1,1,1,1,1,1,0 ],
			[ 1,1,1,0,0,1,1,0 ],
			[ 0,0,0,0,0,0,0,0 ]]

var board = new five.Board();
						
SegOn = 1;
SegOff = 0;	
DigitOn = 0;
DigitOff = 1;
lights = '0001';

function lpad(n, width, z) {
  z = z || '0';
  n = n + '';
  return n.length >= width ? n : new Array(width - n.length + 1).join(z) + n;
}

function loop(){
  //This part of the code is from the library SevSeg by Dean Reading
  for (seg=0;seg<8;seg++) {
    //Turn the relevant segment on
	board.digitalWrite(SegmentPins[seg],SegOn);
 
    //For each digit, turn relevant digits on
    for (digit=0;digit<4;digit++){
	   l = lights[digit]
      if (matrix[l][seg]==1) {
        board.digitalWrite(DigitPins[digit],DigitOn);
      }
      //delay(20); //Uncomment this to see it in slow motion
    }
    //Turn all digits off
    for (digit=0;digit<4;digit++){
      board.digitalWrite(DigitPins[digit],DigitOff);
    }
 
    //Turn the relevant segment off
     board.digitalWrite(SegmentPins[seg],SegOff);
  
  } //end of for		
	
}

//Arduino board connection

board.on("ready", function() {
	console.log('Arduino connected');
	for(p in DigitPins){	
		this.pinMode(DigitPins[p], five.Pin.OUTPUT);
	}
	for(p in SegmentPins){	
		this.pinMode(SegmentPins[p], five.Pin.OUTPUT);
	}
	i = 0
	this.loop(20, function() {
		if (++i == 20) { 
		    i = 0; 
			lights = lpad(parseInt(lights) + 1, 4, '0')
		}
		loop()
	})	
});