# Midterm IoT Project

Name: Quran Karriem

Date: October 12, 2017

## Project: TumbleText

### Conceptual Description

In studying cloud-connected baby monitors (like those from iBaby Labs), I was struck by the combination of potentially useless data flows, ability to affect a child's physical space from the cloud, and generally poor security. The technology also seems to espouse tacit encouragement of absentee parenting. TumbleText is a large, restrictive worn device that sends text messages to parents (and any one subscribed) whenever a child falls down. The physical object/enclosure is large enough that it makes a toddler more likely to fall (so the parent knows the device is doing something). The device uses an accelerometer to detect a fall, and Particle.publish to send data about "speed" or severity of the fall. 

/// Replace with a description of the ***critical / conceptual dimensions of your project***, with specific reference to the key issues it engages.  These should intersect with the issues that have been explored in the readings and discussions during the first half of class:  eWaste, data security/ownership in relation to corporate cloud infrastructures; critical making; surveillance and privacy, etc. ** *How does your project engage with these issues beyond mere instrumentality?* ** ///

### Form

/// Your project should be embodied in a ***physical form*** that reflects, embodies, and/or amplifies those your project's main concepts and ideas.
Explain your design choices here and include images that document your project's material embodiment. ///

**Finished Enclosure:**

![Finished Enclosure](finished_enclosure2.jpg)

**Electronics Exposed:**

![Enclosure with electronics exposed](exposed_enclosure.jpg)

### Technical Details
Hardware used:
* MMA8452Q Accelerometer
* 1 Red, 1 Yellow, 1 Green LED
* Photon RedBoard
* Mini Speaker - PC Mount 12mm 2.048kHz

Code:
[photon.ino](photon.ino)

Wiring Diagram:
![Wiring Diagram](https://github.com/qmkarriem/physical-computing-midterm/blob/master/WiringDiagram.png)

//   
Here you should give an overview of the technical operation of your device, including:
* Explanation of your  
//

You can include code snippets here:

```
Particle.subscribe("Execute", messageParse, MY_DEVICES);
```
