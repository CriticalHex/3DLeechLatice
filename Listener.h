#ifndef LISTENER_H
#define LISTENER_H

#include <algorithm>
#include <audioclient.h>
#include <cmath>
#include <complex>
#include <endpointvolume.h>
#include <iostream>
#include <mmdeviceapi.h>
#include <vector>
#include <windows.h>

__CRT_UUID_DECL(IAudioMeterInformation, 0xC02216F6, 0x8C67, 0x4B5B, 0x9D, 0x00,
                0xD0, 0x08, 0xE7, 0x3E, 0x00, 0x64);

MIDL_INTERFACE("C02216F6-8C67-4B5B-9D00-D008E73E0064")
IAudioMeterInformation : public IUnknown {
public:
  virtual HRESULT STDMETHODCALLTYPE GetPeakValue(float *pfPeak) = 0;

  virtual HRESULT STDMETHODCALLTYPE GetMeteringChannelCount(UINT *
                                                            pnChannelCount) = 0;

  virtual HRESULT STDMETHODCALLTYPE GetChannelsPeakValues(
      UINT32 u32ChannelCount, float *afPeakValues) = 0;

  virtual HRESULT STDMETHODCALLTYPE QueryHardwareSupport(
      DWORD * pdwHardwareSupportMask) = 0;
};

class Listener {
private:
  IMMDeviceEnumerator *pDeviceEnumerator = nullptr;
  IMMDevice *pAudioRenderDevice = nullptr;
  IAudioMeterInformation *pMeterInformation = nullptr;

  IMMDevice *pAudioCaptureDevice = nullptr;
  IAudioClient *pAudioClient = nullptr;
  WAVEFORMATEX *pMixFormat = nullptr;
  IAudioCaptureClient *pCaptureClient = nullptr;

public:
  void getAudioLevel(float *out);
  void initialize();
  Listener();
  ~Listener();
};

#endif