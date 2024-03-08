#include "Listener.h"

using namespace std;

void Listener::initialize() {
  HRESULT hr;

  hr = CoInitialize(NULL);
  if (FAILED(hr)) {
    cout << "Failed to initialize" << endl;
  }

  hr = CoCreateInstance(__uuidof(MMDeviceEnumerator), NULL, CLSCTX_ALL,
                        __uuidof(IMMDeviceEnumerator),
                        (void **)&pDeviceEnumerator);
  if (FAILED(hr)) {
    cout << "Failed to create device enumerator" << endl;
  }

  hr = pDeviceEnumerator->GetDefaultAudioEndpoint(eRender, eConsole,
                                                  &pAudioRenderDevice);
  if (FAILED(hr)) {

    cout << "Failed to get the audio render endpoint" << endl;
  }

  hr =
      pAudioRenderDevice->Activate(__uuidof(IAudioMeterInformation), CLSCTX_ALL,
                                   NULL, (void **)&pMeterInformation);
  if (FAILED(hr)) {
    cout << "Failed to activate meterInformation device" << endl;
  }
}

Listener::Listener() { initialize(); }

Listener::~Listener() {
  pMeterInformation->Release();
  pAudioRenderDevice->Release();
  pDeviceEnumerator->Release();

  CoUninitialize();
}

void Listener::getAudioLevel(float *volume) {
  pMeterInformation->GetPeakValue(volume);
}