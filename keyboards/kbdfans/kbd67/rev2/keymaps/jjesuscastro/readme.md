# jjesuscastro's keymap for kbd67 rev2

This is my personal  keymap for kbd67 rev2. With it is a custom effect for Caps Lock.


## Keymap

### Base Layer
![Base Layer](https://user-images.githubusercontent.com/32050665/93083105-a924b700-f6c4-11ea-8b64-8bb3108c92c1.png)
### FN Layer
![FN Layer](https://user-images.githubusercontent.com/32050665/93083140-c063a480-f6c4-11ea-9488-451955b34aef.png)
<p>* Custom Keycode

## Caps Lock
<p>Enabling caps lock will make the rbg underflow blink on a fixed interval. Pressing 'CAPS Speed -' or 'CAPS Speed +', FN + A or FN + S respectively, will change the interval between blinks.
<p>The RGB Effect that will blink is not a static color. rgblight_toggle() will be called repeatedly hence keeping the currently used RGB Effect.

## VIA Custom Keycodes
<p>Custom keycodes created to adjust Caps Lock Interval Speed remappable through VIA.
<p>Achieved by assigning USER00 to a custom keycode in keymap.c

![keymap.c](https://user-images.githubusercontent.com/32050665/112081381-87017980-8bbe-11eb-9220-786dd16d78f6.png)

*If the keymap is VIA enabled, assign USER00 to the first custom keycode, if not, assign SAFE_RANGE.*

And adding customKeycodes in the via.json script (look for the original file in https://github.com/the-via/keyboards/tree/master/src)

![via.json](https://user-images.githubusercontent.com/32050665/112081441-a0a2c100-8bbe-11eb-9715-bede894d298f.png)

*The definition of the custom keymaps in the via.json should be in the same order in the custom_keycodes enum.*

<p>Import the via.json file into VIA after the keyboard has been detected. If done correctly custom keycodes should be visible in VIA under a new CUSTOM tab.

![VIA](https://user-images.githubusercontent.com/32050665/112081404-91237800-8bbe-11eb-8695-5b9c1a871c5f.png)
