

%----------------- levantando controlador ---------------------------------

R = 0.5*10^(3); %R = 1Mohns
C = 1*10^(-3); %C =  1uF

%função de transferencia (continua)
num = [1/(R*C)];
den = [1 (1/(R*C))];
G = tf(num,den)

%função de transferencia (discreta)
G_d = c2d(G,0.001)

%projeto controlador
pidTuner(G_d)

