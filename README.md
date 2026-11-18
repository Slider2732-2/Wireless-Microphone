A simple project to create a usable wireless microphone.
<br>
The working system in development uses an ESP32 Audio Kit V2.2 and a Linux PC. <br>
Range without packet loss is approximately 200ft. Suitable for around the house and recordings made outside around the house.<br>
The aim, is to reduce the footprint and increase the functionality, incorporating a SSD1306 screen for WiFi strength and other data and using a PCM1808 ADC for the analog to digital encoding. . <br>
A more regular ESP32 is intended in the next stage, a repurposed ESP32-CAM, to bring down the final size. <br>
<br>
<br>
Several factors may determine successful running of the project at this stage:<br>
Python3 has been used, which entails you have an up to date Python environment. <br>
You may have to run the receiving code in a virtual environment - which is outside of the scope of this Github repository. Basically, online help will certainly allow the copy and paste of the few commands to get the Python code to run. That situation should resolve issues away from Linux, for Windows and Mac PC's. 
Your ESP32 Audio Kit should be running the AC101 CODEC. Though, the ES8388 can certainly be used by replacing the AC101 specific calls.  
<br>
<br>
<br>
ESP32_AudioKit_AudioSender.ino should be uploaded to the ESP32 Audio Kit V2.2
<br>
udp_audio-AudioKit.py should be run from the terminal, inside the directory where the file is located.
<br>
<br>
<br>
Specs are - <br>
Quality: 16KHz, 16 bit transmission and reception <br>
Range: approx 200ft (largely dependent on Wifi router power, location, local conditions) <br>
Packet loss: None to very low within the expected WiFi range <br>

