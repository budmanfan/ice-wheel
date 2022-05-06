%% Ice Wheel - Control design %%
clc;
% ice-wheel
m_w = 7.2; % kg
r_w = 0.127; % m
J_w = 1/2*m_w*r_w^2;

% chassis
m_batteries = 28*67e-3 + 0.2; % kg (cells + bms?)
m_mot_contr = 0.5; % kg
m_c = 3 + m_batteries + m_mot_contr; % kg
l_c = 0.02; % m -> COG of chassis is assumed to be in the center
h_base = 0.1;
w_base = 0.75;

% rider
m_r = 65; % kg
h_r = 1.7; % m
d_r = 0.2; % m
l_r_ = h_r * 0.55; % approximation of COG of human
l_r = l_r_ + h_base/2; % COG of rider from axel

g = 3.81; % m/s^2

% total
m_t = m_w + m_c + m_r; % kg
l_t = (l_r*m_r + l_c*m_c) / m_t; % m
J_t = 1/12*m_r*(h_r^2+d_r^2) + 1/2*m_c*l_c^2 - J_w;

disp(['Center of gravity distance from wheel axis:  ', num2str(l_t, 2), ' m']);
disp(['Total inertial moment of vehicle:            ', num2str(J_t, 3), ' kgm^2']);

