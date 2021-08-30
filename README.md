Here I am recording my progression from research to prototyping to a final working design of my glucometer. 
# 1. Research
Using the dielectric value of blood varied by glucose to measure capacitance has been an establish, tried and unsuccessful method of measuring glucose. It was only once I stumbled upon this paper "https://aip.scitation.org/doi/pdf/10.1063/1.5116059" I realized this research team has validity to a new method of measuring blood glucose. 

Their main principle work on several new realizations

a. Instead of using a static voltage, a low frequency (1khz) waveform was used to which the impedance correlates linearly with glucose concentration 

b. By using a sine wave instead of a static dc voltage, the flaws of the previously established methods are gone such as stray capacitance effect, 
    and other noise like other conductor vicinity effect. Though noise is not as much of an issue in this setup a band pass filter is used in case of 
    extraneous cases. 

# 2. breadboard prototyping and proving their research 
I designed my own circuit based on the paper's unusual way they use an op-amp.

![](https://github.com/chrisshum/capacitive-glucometer/blob/main/Wikimages/circuit.PNG)

On the left you can see the 555 timer I used to create square waves following with op-amps to bias the square wave from 0-5v to -2.5v to 2.5v. Next the waveform goes through three low pass filters to become the 1khz sinewave that I used as my input signal.
The signal waveform now would go though the two capacitors at the top 20pf for human finger, and 0.3pf for the same capacitor but without the finger. It then needs to get converted from a sine wave to a stable voltage signal. 
At the bottom I created two full wave rectifiers to convert the signal to a positive voltage, then I used capacitor smoothing to bring the voltage values to a stable voltage that the ADC pins on a microcontroller can read. 
![](https://github.com/chrisshum/capacitive-glucometer/blob/main/Wikimages/breadboard%20circuit.jpg)

This circuit theoretically worked but I had to make it on a breadboard to make sure it works in reality. 
Most everything worked out well except it was difficult to create a negative voltage source. Eventually I was able to fix this with an charge pump DC-to-DC voltage converter TC7660 after failed attempts to make a high enough capacity out of capacitors and diodes. 
As for the op-amps I was able to use LM358N for any parts of the circuit that required an op-amp.

# 3. design of physical capacitor 

![](https://github.com/chrisshum/capacitive-glucometer/blob/main/Wikimages/fingercapacitor.jpg)

I began with using the same methods of the paper to create a capacitor by placing copper plates on a silicone finger sleeve. This was to make sure I can reproduce their values when measuring. I realized this was a horrible modality to measure as people with varying finger girth changed the distance between the semicircular capacitor and therefore the measured capacitance. 

![](https://github.com/chrisshum/capacitive-glucometer/blob/main/Wikimages/diagramcylindralcircuit.PNG)
![](https://github.com/chrisshum/capacitive-glucometer/blob/main/Wikimages/equationcylindralcircuit.PNG)

Based on the paper https://aip.scitation.org/doi/pdf/10.1063/1.495846, Changing the distance between the two cylinders greatly affects the capacitance by changing theta. But that is not the worst part by pushing two static plates apart with a girthy finger the plates no longer form a perfect circle and more like an ellipse this inconsistence gave me a varied reading between different subject hands enough to completely ruin the linearity of the blood glucose.

![](https://github.com/chrisshum/capacitive-glucometer/blob/main/Wikimages/wristcapacitor.jpg)
I instead decided to design a way to encapsulate the plates with a more consistent distance. I ended up designing a wrist band which the plates are encapsulated in a single layer of electrical tape. The wrist watch is designed to cinch on any point of the forearm that it is snug which helps eliminate the variability of wrist girth if you have a more girthy arm it would be more distal closer to the hand and if you are skinnier it would be more proximal toward the elbow. I calculated the total surface area of the plates and plugged in the equation to maintain the same capacitance as if it were a finger capacitor however it had a much more consistent measurement and was much easier to put on than the tight finger glove. 

# 4. using a esp 32 microcontroller 
![](https://github.com/chrisshum/capacitive-glucometer/blob/main/Wikimages/microcontoller.jpg)
Eventually I needed to pick a controller to run this circuit, and I discovered there were microcontrollers that are able to perform DAC conversion and I can make a sine wave without my 555 timer op-amps and low pass filters which cut my circuit parts in half. I also needed to transmit data live and decided to use Bluetooth to transfer to my phone and laptop to record data of blood sugar over time. 
![](https://github.com/chrisshum/capacitive-glucometer/blob/main/Wikimages/microcontoller%20with%20circuit.jpg)
Here is the final circuit with a battery sources mounted on top of the wrist capacitor so it is all in one package. 
# 5. Next steps 
![](https://github.com/chrisshum/capacitive-glucometer/blob/main/Wikimages/glucometer%20v2.png)
Eventually I'll be printing out my circuit on a small pcb and encapsulate everything in a silicone cast so that it is all in one professional package.

Next steps is to 
1. Finish putting the new circuit on Altium and design and print a PCB to put it on. 
2. Convert my sine wave generator from a dedicated thread on the proccessor to utilizing the DMA as good practice to not use too many limited resources on a board. 
3. use the Wifi module so I can share data anywhere in a home within range of the router rather than just the bluetooth range of the device.
4. Possible migration to a more well documented board like a stm32. 


