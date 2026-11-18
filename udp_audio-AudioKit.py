
import socket
import sounddevice as sd
import wave

UDP_PORT = 12345
RECORDING_FILE = "audio_kit_capture.wav"

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
sock.bind(("0.0.0.0", UDP_PORT))

print("Waiting for ESP32 Audio Kit...")

with wave.open(RECORDING_FILE, "wb") as wav:

    wav.setnchannels(2)
    wav.setsampwidth(2)       # 16-bit audio
    wav.setframerate(16000)   # 16 kHz

    with sd.RawOutputStream(
        samplerate=16000,
        channels=2,
        dtype="int16",
        device=9
    ) as audio:

        print("Audio playback and recording started!")
        print("Recording to:", RECORDING_FILE)
        print("Press Ctrl+C to stop.")

        try:
            while True:
                data, addr = sock.recvfrom(4096)

                # Audio Kit packets: 1280 bytes
                if len(data) == 1280:
                    audio.write(data)
                    wav.writeframesraw(data)

        except KeyboardInterrupt:
            print("\nRecording stopped.")

sock.close()
print("WAV file saved successfully.")

import socket
import sounddevice as sd

UDP_PORT = 12345

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
sock.bind(("0.0.0.0", UDP_PORT))

print("Waiting for ESP32 audio...")

with sd.RawOutputStream(
    samplerate=16000,
    channels=2,
    dtype="int16",
    device=9
) as audio:

    print("Audio playback started!")

    while True:
        data, addr = sock.recvfrom(4096)

        if len(data) % 4 == 0:
            audio.write(data)
