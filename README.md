# Zenray

*BRIGHTEN YOUR MIND*

A portable light therapy device that uses researched frequencies to lessen users' anxiety, depression and insomnia symptoms. We will use a device consisting of 9-12 white led lights, controlled by arduino and program 2-3 presets for our MVP that focus on different areas (amusement and stress relief, insomnia relief). The programmes will be based on extensive research in the area that has been carried out since the 70s, our unique selling point is that the device is affordable and portable (similar solutions cost up to 2000 euros on the market right now and are tedious to set up), possibly syncable with music.


## The Problem
As mentioned in the description, the problem we are trying to solve is the lack of affordable and portable light therapy devices. The current solutions are either too expensive or too bulky to be used on the go. Our solution is to create a device that is both affordable and portable.


## Components
To build the device, we will need the following components:

| Component           | Quantity |
|---------------------|----------|
| MAX72xx             | 2        |
| Red LED             | 1        |
| Yellow LED          | 1        |
| $1k\omega$ Resistor | 3        |
| Photo-resistor      | 1        |
| NPN Transistor      | 1        |
| Jumper Buses        | 25       |
| Simple Jumpers      | 10       |
| Breadboards         | 1-2      |
| Cardboard Headset   | 1        |
| ESP 32              | 1        |

**Total Cost:** ~38 Euros

With the above components, we will be able to build the device. The device will be controlled by the ESP 32, which will be connected to the MAX72xx. The ESP 32 will be connected to the internet and will be able to be controlled via a web interface. The web interface will be hosted on the ESP 32 itself.


## Circuit Diagrams
The project consists of two main circuits, one to control the MAX72xx and one to control the LED. The MAX72xx circuit is based on the [MAX7219](https://how2electronics.com/8x8-led-matrix-max7219-arduino/) and [ESP 32](https://www.espressif.com/sites/default/files/documentation/esp32_datasheet_en.pdf). The led circuit does not rely on any external components, it is just a simple circuit to control the led with a transistor.

![arduino](./circuit_ard.svg)

![led](./circuit_led.svg)

### Inputs and Outputs
For the display, the inputs are a bit more abstract:

| Program   | Result                                           |
|-----------|--------------------------------------------------|
| Amusement | The display will show a random pattern of lights |
| Relief    | 10HZ frequency                                   |

And for the led, the inputs are:
| Input            | Result  |
|------------------|---------|
| Hight Lumniocity | LED ON  |
| Low Lumniocity   | LED OFF |

LED Simulation: [link](https://www.tinkercad.com/things/hfVYoatWuRI?sharecode=ZBD9FycEfKoT8tPLrLQteGDT8PjNM_R2r0t22P-xDYU)


## Research

**Red light therapy helps boost ATP production which is lowered in the case of depression and anxiety disorders**

Red light therapy or photobiomodulation has been increasing in popularity over the last few years. The most well studied mechanism of action of PBM centres around cytochrome c oxidase (CCO), which is unit four of the mitochondrial respiratory chain, responsible for the final reduction of oxygen to water using the electrons generated from glucose metabolism [10]. The theory is that CCO enzyme activity may be inhibited by nitric oxide, especially in damaged cells. In order to dissociate NO in the mitochondrial respiratory chain, photons are needed that will be absorbed by CCO, the absorption peaks for photons are in the red (600-700nm) and infrared (760-900nm) spectral region which means that red light therapy direectly encourages the dissociation of NO and in return rises the membrane potential of mitochondria, allowing for an increase in glucose metabolization and ATP production(Hamblin M. R. (2016). Shining light on the head: Photobiomodulation for brain disorders. BBA clinical, 6, 113–124. https://doi.org/10.1016/j.bbacli.2016.09.002). This is significant, as lowered ATP production is a hallmark of many neurological conditions such as major depressive disorder, traumatic brain injury, Parkinson’s disease, and Alzheimer’s disease. (Hennessy, M., & Hamblin, M. R. (2017). Photobiomodulation and the brain: a new paradigm. Journal of optics (2010), 19(1), 013003. https://doi.org/10.1088/2040-8986/19/1/013003). Red light is also most efficient in entering and simulating the brains gamma waves when administered through visual perception. (Lee, K., Park, Y., Suh, S.W. et al. Optimal flickering light stimulation for entraining gamma waves in the human brain. Sci Rep 11, 16206 (2021). https://doi.org/10.1038/s41598-021-95550-1).

**Flickering light therapy works faster than antidepressants to cure symptoms of depression and helps with mindfulness**

Many of the current therapies for mood disorders such as depression, SAD, anxiety and insomnia consist of pharmaceutical involvement in the form of antidepressants or other mood enhancers and/or psychiatric counselling. These however can have adverse side effects and aren't always cost and time efficient. Recently light therapy has begun to be considered as an effective tool for the treatment of the neuropsychiatric behaviours and symptoms of a variety of brain disorders or diseases, including depression. One of the most effective forms of light therapy is flickering photic stimulation at alpha frequencies which has been proven to improve behavioural performance in depressed individuals faster than fluoxetine, a common antidepressant (Kim, S., Kim, S., Khalid, A., Jeong, Y., Jeong, B., Lee, S. T., Jung, K. H., Chu, K., Lee, S. K., & Jeon, D. (2016). Rhythmical Photic Stimulation at Alpha Frequencies Produces Antidepressant-Like Effects in a Mouse Model of Depression. PloS one, 11(1), e0145374. https://doi.org/10.1371/journal.pone.0145374). In addition to mood enhancing effects, flicker light stimulation induces short-term alterations in consciousness including hallucinations and geometric patterns, similar to those induced by psychedelic substances with nonexistent to minimal side effects. This has been reported to create a spiritual and unity experience, boost insightfulness and bliss (Bartossek, M. T., Kemmerer, J., & Schmidt, T. T. (2021). Altered states phenomena induced by visual flicker light stimulation. PloS one, 16(7), e0253779. https://doi.org/10.1371/journal.pone.0253779). By producing gamma waves with flickering, in a receptive state the therapy has similar effects to those of meditating, improving cognitive function and balancing brain waves to combat insomnia and stress. (Braboszcz, C., Cahn, B. R., Levy, J., Fernandez, M., & Delorme, A. (2017). Increased Gamma Brainwave Amplitude Compared to Control in Three Different Meditation Traditions. PloS one, 12(1), e0170647. https://doi.org/10.1371/journal.pone.0170647)


## Our program - novel combination of red flickering light therapy

Zenray is a novel product on the market that combines the repairing benefits of red light therapy with mood enhancing effects of flickering light therapy. The MVP comes with 3 presets. The “amusement” program in the Zenray device that focuses on amusement and stress relief. It is a list of arrays (x,y) that will be lit up in a loop. The first element is the x coordinate, and the second is the y coordinate. The program contains 50 points with x and y coordinates. Each point on the LED matrix will be lit up in a specific sequence that flickers at an alpha frequency, creating a moving light pattern that is designed to be visually stimulating whilst the red LEDs used also simulate the creation of gamma waves in the brain, improving cognitive abilities.


## Code

All the necessary code to flash is in `program.ino`. Once you flash the code, you should check the *serial console* for the connection IP. Then you can connect to the device via the browser and navigate to the `/` endpoint to see the main page. All will be explained there.
