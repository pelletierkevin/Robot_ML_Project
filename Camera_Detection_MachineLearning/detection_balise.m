clear all;
close all;
clc;

load('weights_gray.mat');
path = sprintf('new_data/rond/im_rond (147).jpg');



img = imread(path);


img = imresize(img, [168 300] );
imagesc(img);
img = double(rgb2gray(img));
imgvec = img(:)';
imgvec = (imgvec-mean(imgvec))/255;

predict(Theta1, Theta2, imgvec);

load('newdata_forme_reg.mat');
X = double(Xdata);
y = ydata;
m = size(Xdata,1);
result = predict(Theta1, Theta2, X);   
result==y;
efficiency = 100*sum(result==y)/m;