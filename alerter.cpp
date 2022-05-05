#include <iostream>
#include <assert.h>

int alertFailureCount = 0;
#define MAXTHRESHOLDTEMPERATURE 37.2

int networkAlertStubOK(float celcius) {
	std::cout << "ALERT: Temperature is " << celcius << " celcius. - OK\n";
	// Network stub to always return true 
	return 200;
}

int networkAlertStubNOK(float celcius) {
	std::cout << "ALERT: Temperature is " << celcius << " celcius. - NOK\n";
	// Network stub to always return false
	return 500;
}
int networkAlert(float celcius) {
	//Real network alert
	std::cout << "ALERT: Temperature is " << celcius << " celcius.\n";
	if (celcius >= MAXTHRESHOLDTEMPERATURE)
	{
		return 200;
	}
	return 500;
}

float farenheitToCelciusConverter(float farenheit)
{
	float celcius = (farenheit - 32) * 5 / 9;
	return celcius;
}

void alertInCelcius(float farenheit, int(*networkAlerterFunc)(float)) {
	float celcius = farenheitToCelciusConverter(farenheit);
	int returnCode = networkAlerterFunc(celcius);
	if (returnCode != 200) {
		// non-ok response is not an error! Issues happen in life!
		// let us keep a count of failures to report
		// However, this code doesn't count failures!
		// Add a test below to catch this bug. Alter the stub above, if needed.
		alertFailureCount++;
	}
}

void testAlertInCelcius(float farenheit,int(*networkAlerterFunc)(float),int expectedFailureCount)
{
	alertInCelcius(farenheit, networkAlerterFunc);
	assert(alertFailureCount == expectedFailureCount);
}

int main() {
	testAlertInCelcius(400.5, &networkAlertStubNOK,1);
	testAlertInCelcius(303.6, &networkAlertStubNOK,2);
	testAlertInCelcius(99.0, &networkAlertStubOK,2);
	testAlertInCelcius(96.0, &networkAlertStubOK,2);
	testAlertInCelcius(200.0, &networkAlertStubNOK,3);
	std::cout << alertFailureCount << " alerts failed.\n";
	std::cout << "All is well (maybe!)\n";
	return 0;
}
