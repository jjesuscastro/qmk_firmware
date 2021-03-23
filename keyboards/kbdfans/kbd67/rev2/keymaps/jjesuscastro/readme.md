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
![keymap.c](https://github.com/jjesuscastro/qmk_firmware/blob/f766563b6e33ea679026c99cc6db058fc766203b/keyboards/kbdfans/kbd67/rev2/keymaps/jjesuscastro/keycode.png)
*If the keymap is VIA enabled, assign USER00 to the first custom keycode, if not, assign SAFE_RANGE.*

And adding customKeycodes in the via.json script (look for the original file in https://github.com/the-via/keyboards/tree/master/src)
![via.json](https://github.com/jjesuscastro/qmk_firmware/blob/f766563b6e33ea679026c99cc6db058fc766203b/keyboards/kbdfans/kbd67/rev2/keymaps/jjesuscastro/via.png)
*The definition of the custom keymaps in the via.json should be in the same order in the custom_keycodes enum.*

Import the via.json file into VIA after the keyboard has been detected.

<p>If done correctly custom keymaps should be visible in VIA under a new *CUSTOM* tab.
![VIA](https://github.com/jjesuscastro/qmk_firmware/blob/0ce992994d0d88666f05614f377980148ef7edab/keyboards/kbdfans/kbd67/rev2/keymaps/jjesuscastro/via.png)
