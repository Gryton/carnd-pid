# CarND-Controls-PID
Self-Driving Car Engineer Nanodegree Program

This project is implementation of PID controller, that controls steering of the car around Udacity track simulation. Purpose is to have a car, that will drive the whole track without getting off the road
or popping up onto ledges.

---

## Rubric points reflection

### 1. Describe the effect each of the P, I, D components had in your implementation.

Proportional, *P*, component has very basic influence on the car steering - if car error raises a little it will correct steering a little, if it's bigger raise the correction is bigger. 
As it was expected, increasing *P* coefficient leads to bigger oscillations of the car. It's good for starting point, but the car behaves very nervous, and driving is very sharp. Also the car had tendency
to getting off the track, as it sometimes counter-steered with maximal value, what lead to over-steering so oscillations were getting bigger.
I started with coefficient 1 for P, but as long as I had progression on *D* and I coefficients leading to more smooth driving I was reducing the value for P. I even tried to get rid of proportional part
to see how it goes, but performance of algorithm without proportional part is also not so good - the car reacts too slow for changes, and cannot make fast and small corrections.

Differential component, *D*, made a ride much more smooth. Using just *P* and *D* I was able to drive the whole track. I found that nature of *D* is sometimes very close to *P* - when it's used with too big 
coefficient (even though *P* is small) it also leads to oscillations and can increase them, what wasn't expected by me. For sure differential part is what can really help when CTE is quite big. As proportional
part 'panics' and makes very strong correction when error is big, differential part can just correct new errors, and prevent too big corrections.

Integral component, *I*, was the biggest game changer for me. It was the part that made the car driving really smoothly, and a lot closer to human driving. Increasing it too much, while keeping other
components low also leads to oscillations - and what is understandable, each one is bigger, as sum of error increases rapidly, while reaction is delayed, what leads to too big and too long reaction.
This component can really turn - if you think about that, it's designed for turning - when the car goes off from the middle of the track because of the turn, the differential is rather constant. 
Proportional component could help here, but I want to keep it not too big as it will create oscillations, so there comes integral. In a turn, when car is going straight, sum of error grows rapidly, so it will correct steering
slightly, until it will zero after driving stably in the middle, or driving to the inside of a turn in case of sharper corners. When increasing integral coefficient I could reduce *P* and still have good
corrections, without oscillations. Main difference is that using more integral than proportional the reaction is delayed, but smoother.

### 2. Describe how the final hyperparameters were chosen.

I've started tuning manually with mainly *PD* controller with coefficient *I* very close to 0. I've played around a bit, as long as I saw that increasing *D* helps with reducing oscillations, and then added very
small *I* coefficient. I reduced both *P* and *D*, and when I got oscillations I've increased *D* to prevent them. I was trying to minimize total error calculated as sum of absolute values of errors got
during the whole track, and watched how the car goes through the track. I realized, that what I liked not necessarily was seen in total error. Sometimes error increased, but thought that the car was
driving better, and I had much less motion sickness. So I thought that it will be quite nice to go this way, without twiddling around total error. My last result has much worse total error, and it's
visible that it sometimes goes closer to lane lines, but I think it drives more natural and I like it better this way.
I think that creating good PID for self-driving car should also contain minimizing integral of steering angle differences, so the ride will be accurate in terms of CTE and smooth, without sharp
left to right transitions, just like a human does.
