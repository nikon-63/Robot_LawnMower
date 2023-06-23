# Robot lawn mower

<p align="center">
  <img src="/Image/RobotMower_Main_IMG.png" width=50% height=50%>
</p>

## Overview 

This repository shows my journey of designing and building a robot lawn mower. My previous Robot Hand project provided me with a basic knowledge of robotics and microcontroller, which was further developed in this more ambitious project. In particular, skills relating to networking and hardware control were developed.

The project focused on modifying a Westwood Ti200 ride-on lawn mower, utilising linear actuators and motor controllers for steering and brake control. An ESP8266 microcontroller with built-in Wi-Fi has been used for wireless control, and a custom Python program and iOS app were created for controlling the lawn mower. The project emphasised problem-solving and iterative design, resulting in the fabrication of custom 3D-printed parts for improved functionality. The skills developed in this project provide a strong foundation for future projects, and the robot provides a base to explore other technologies, such as AI and different location positioning systems.


## Skills developed
1.	**CAD Design and 3D Printing:** Using Fusion 360 to design custom parts for the robot lawn mower to be printed, thus improving functionality.
2.	**Prototyping:** Experimenting and trying different approaches to solve a problem or improve a design leading to robust hardware and software.
3.	**Arduino/Microcontrollers:** Skills working with microcontrollers to interface with various sensors and control the robot's movements.
4.	**Python Programming:** Skills in handling network connections within Python, both for the Python app and the Raspberry PI Pico-based controller.
5.	**C++ Programming:** Hands-on experience working with the ESP8266 microcontroller and motor controllers. Practically within the Arduino environment. 
6.	**Swift App Development:** Building on pre-existing basic knowledge of Swift to develop more complex iOS applications.
7.	**Networking and Web Requests:** Strong understanding of web requests and network communication protocols.
8.	**Analog Input Handling:** Understanding the use of ADC to process analogue inputs to provide precise position feedback for the robot's steering mechanism.




## Process
For several compelling reasons, the Westwood Ti200 ride-on lawn mower was carefully selected as the ideal base for the project. I had previously thoroughly restored its engine and transmission, providing me with a solid understanding of its mechanics. Additionally, the sturdy metal frame and its boxy design offered excellent mounting options for all the necessary components.

The initial plan used a linear actuator with a servo for the wheels and brake, respectively. However, upon receiving the 25 kg servo, it became evident that it was severely underpowered, rendering it incapable of activating the brake. To address this issue, a second linear actuator was incorporated into the design.

### Steering
To begin, the existing steering rod was replaced with one of the actuators, with the base securely mounted beneath the fuel tank holder. Connecting the opposite end posed a challenge as it required the ability to adjust the distance between the actuator and the preexisting steering rod for proper alignment. Overcoming this hurdle involved designing a custom 3D-printed adapter to accommodate a 12M threaded rod. The other end of the rod featured a ball joint connected to the pre-existing steering arm. 

| Stearing Actuator | Stearing Demo |
| ---------------------- | ---------------------- |
| <img src="/Image/Stearing_actuator.jpeg" width=220px height=300px> | <img src="/Image/Stearing_Moving.gif" width=220px height=300px> |

### Microcontrollers
Subsequently, efforts shifted toward controlling the robot. Initially, an Arduino Uno with a serial connection was used. However, to achieve wireless control and eliminate the need for a physical cable, a switch was made to the ESP8266, which offered built-in Wi-Fi capabilities that I had previously explored in my robot hand project. The L298N motor controller was also implemented to link the actuators to the ESP8266 due to its compact size and dual motor control capabilities.

| ESP8266 | L298N |
| ---------------------- | ---------------------- |
| <img src="/Image/Hardware.jpeg" width=220px height=300px> | <img src="/Image/L298N.jpeg" width=220px height=300px> |


### Web Server 
A temporary web server was set up on the ESP8266 in AP mode, enabling wheel position to be manipulated through a web interface for testing. Nonetheless, the limited power of the ESP8266 resulted in sluggish response times, making it unresponsive. Interestingly, using the curl command on a Mac proved to be more efficient. As a result, a Python program utilising the request library was devised to control the movement.

### Braking 
The second actuator was mounted to the footrest for brake control, and a custom 3D-printed claw was affixed to its other end to engage the brake pedal. To ensure swift braking in emergencies, the brake pedal needed to be slightly depressed just before reaching the activation point at all times. This will minimise the actuator's travel distance and result in faster braking times. Since the actuator lacked position control like a servo motor, a button was integrated at its base. This button was triggered by a 3D-printed component on the extension tube, effectively stopping the actuator's movement. The position of the stopping point could be adjusted by moving the 3D-printed part along the extension tube.

| Braking System | Braking Demo |
| ---------------------- | ---------------------- |
| <img src="/Image/Braking_System.jpeg" width=320px height=220px> | <img src="/Image/Bracking_Demo.gif" width=220px height=300px> |

### Integration Testing And Development   
Initial tests with the Python program revealed difficulties in controlling the steering. Compared with operating an RC car, you can gauge the wheels' position based on where you push the joystick, and when the joysticks are released, the wheels return to the centre. This made it clear that incorporating more position feedback and implementing an auto-wheel centring mechanism was needed to improve the robot’s handling.

Custom 3D-printed gears were designed to fit around the steering column and a potentiometer, enabling precise position feedback. This numerical feedback could easily be changed into a visual representation, optimising the user experience. Additionally, this enabled the ESP8266 to align the wheels to the centre position automatically.

| Potentiometer System |
| ---------------------- |
| <img src="/Image/Potentiometer.jpeg" width=403px height=302px> |

### IOS App and Raspberry Pi Pico Controller
To complete the project, the Python program was replaced with a custom iOS app for controlling the robot using an iPhone. A handheld controller was also developed using the new Raspberry Pi Pico W as an alternative way of controlling the robot.

| IOS App | PICO W |
| ---------------------- | ---------------------- |
| <img src="/Image/IOS.PNG" width=200px height=370px> | <img src="/Image/Pico.png" width=200px height=370px> |


### Conclusion
This project serves as a platform for learning and skill development. Future plans involve exploring GPS and a local positioning system (LPS) to enhance my understanding of the technology and explore potential use cases. Furthermore, the intention is to delve into artificial intelligence and develop a system capable of distinguishing between long and short grass, aiming to achieve full autonomy for the lawnmower.

