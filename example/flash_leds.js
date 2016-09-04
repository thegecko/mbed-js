var check = 0;
var led = 0;

// Setting the pin to 0 turns the LED on
var led_off = 1;
var led_on = 0;

var digital_outs = [];

var leds = [LED1, LED2, LED3, LED4];

function connect_pins()
{
  print("Creating new DigitalOuts");
  digital_outs = [];
  for (var i = 0; i < 4; i++)
  {
    digital_outs.push(DigitalOut(leds[i], led_off));
    if (digital_outs[i].is_connected())
    {
      print("LED " + i + " is connected.");
    }
    else
    {
      print("LED " + i + " is not connected.");
    }
  }
}

connect_pins();

function blink()
{
  var blk = (check >= 8) ? led_on : led_off;

  digital_outs[0].write(led_off);
  digital_outs[1].write(led_off);
  digital_outs[2].write(led_off);
  digital_outs[3].write(led_off);

  digital_outs[led].write(blk);

  if (check === 9)
  {
    print("Finished with LED " + led);
    led = (led + 1) % 4;
    if (led === 0)
    {
      connect_pins();
    }
  }

  check = (check + 1) % 10;
}

var button = InterruptIn(SW2);
button.fall(function() {
  print("YOU PUSHED THE BUTTON!");
});

print("blink.js has finished executing.");

module.exports = blink;