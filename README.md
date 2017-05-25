# arduino-buttons-example
Example sketch that handles button events using normally closed momentary contact buttons.

In this example, two NC momentary contact buttons are hooked up to pins {A0, A1} and {A4, A5}.

The Buttons class detects when one or both buttons have been pressed and released, triggering the buttonEvent method.
The button event provides the button(s) pressed and the amount of time in milliseconds the button was held down for.

In this sketch, a button event is considered valid if the button was pressed and held for at least 140 milliseconds but no longer than 2000 milliseconds.  I have a maximum of 2 seconds to prevent sticky button from occuring from a faulty button or interference from the air.

Example Output:

[Button] button 1	Duration: 155
[Button] button 2	Duration: 171
[Button] button 1	Duration: 144
[Button] both	Duration: 173
[Button] button 1	Duration: 155
[Button] button 2	Duration: 202
[Button] button 1	Duration: 141
[Button] button 1	Duration: 142
[Button] both	Duration: 325
[Button] both	Duration: 735
[Button] both	Duration: 207
[Button] both	Duration: 172
[Button] both	Duration: 229
[Button] button 1	Duration: 165
[Button] button 2	Duration: 236
[Button] button 2	Duration: 935
[Button] button 2	Duration: 494
[Button] button 2	Duration: 153
[Button] button 2	Duration: 164
