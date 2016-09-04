var blink = require( "./flash_leds" );

function sysloop ()
{
  blink();
}

// Call sysloop every 100ms
var ticker = Ticker();
ticker.attach(sysloop, 0.1);

print("main.js has finished executing.");
