### Introduce

Iwown's BLE device software developer tools in iOS platform.
This SDK can help you quickly build apps and establish connections and communicate with Iwown's Bluetooth devices.


### Major

* "AutumnHeader.h" contains important Macro and Enum.
* "BLEAutumn.h" implements an instance of CBCentralManager, managing Bluetooth status, searching and connecting.
* "BLEquinox.h" introduces the delegation method of communication.
* "BLESolstice.h" lists the active methods of the app.
* "ZRHealthData.h" is the underlying model of the data.
* "ZRModel.h" is the base model for device settings.

### How to Use

Initialize with the following code, remember to keep a strong reference.
```
self.bleAutumn = [BLEAutumn midAutumn:BLEProtocol_Any];
self.bleAutumn.discoverDelegate = self;
self.bleAutumn.connectDelegate = self;
[self.bleAutumn isBound];
```

### Programming language
Both support for Objective-C && Swift.
