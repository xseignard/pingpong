const noble = require('noble');
const osc = require('node-osc');

const client = new osc.Client('127.0.0.1', 12345);

const ids = {
	uuid: 'c89694e52602',
	serviceUUID: '6e400001b5a3f393e0a9e50e24dcca9e',
	rxCharacteristic: '6e400003b5a3f393e0a9e50e24dcca9e',
	txCharacteristic: '6e400002b5a3f393e0a9e50e24dcca9e',
}

const sendMessage = (raquette, value) => {
	client.send(`/${raquette}`, value);
};

noble.on('stateChange', (state) => {
	if (state === 'poweredOn') noble.startScanning();
	else noble.stopScanning();
});

noble.on('discover', (peripheral) => {
	console.log(peripheral.uuid);
	if (peripheral.uuid === ids.uuid) {
		console.log(`uuid: ${peripheral.uuid} // local name: ${peripheral.advertisement.localName}`);
		noble.stopScanning();
		peripheral.connect(() => {
			console.log('connected!');
			peripheral.discoverServices([], (error, services) => {
				const uartService = services.filter((service) => { return service.uuid === ids.serviceUUID })[0];
				uartService.discoverCharacteristics([], (error, chars) => {
					const rxCharacteristic = chars.filter((char) => { return char.uuid === ids.rxCharacteristic })[0];
					rxCharacteristic.on('read', (state) => {
						const value = parseInt(state.toString());
						if (value > 500) {
							sendMessage(peripheral.advertisement.localName, value);
						}
					});
					rxCharacteristic.notify(true);
				});
			});
		});
	}
});
