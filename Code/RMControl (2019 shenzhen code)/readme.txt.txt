2019 Robomaster competition. Programs for all robots. 
Queen's Knight, Queen's university
Xiaoyi Wang, University of Toronto
More documatations to explain further details will be released sooner. 

Sentry:

1. Sentry-1 is the sentry automatic control system with a random path generator but no slow break and slow acceleration method.

2. Sentry-2 is the sentry automatic control system with slow break and slow acceleration method but no random path generator. (Successfully used during the competition)

PS: Without slow break and slow acceleration method, the sentry may have big error on distance estimation by using motor encoders since the sentry rail is slippy. See application/chassis_task.c and components/modules/chassis.c



EngineerControl:

Chassis control is in application/chassis_task.c. Grip and box control is in application/rc_light.c




Power Limitation method:
For the programs of infantries and the hero: MDK-ARM/app/chassis_task.c: line 311-360

Heat limitation method:
For the programs of infantries and the hero: MDK-ARM/app/shoot_task.c: line 228-243


