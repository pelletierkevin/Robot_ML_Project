clear all;
close all;
clc;

load('newdata_forme.mat');

moyenne = mean(Xdata')';
newXdata = Xdata;
for i =1:50400
 newXdata(:,i) = newXdata(:,i) - moyenne;


end

newXdata = newXdata /255;
Xdata = newXdata;

save('newdata_forme_reg.mat', 'Xdata', 'ydata', '-v7.3');