clear all;
close all;
clc;

Xdata = double(zeros(1460,50400)); % 
ydata = zeros(1460,1);

index = 1;

disp('Carre\n');
for i=1:266 % carre

        outputString = sprintf('new_data/carre/im_carre (%d).jpg',i);
   
    img = imread(outputString);
    
%     r = img(:,:,1);
%     r = r(:);
%     
%     g = img(:,:,2);
%     g = g(:);
%     
%     b = img(:,:,3);
%     b = b(:);
    
    img = rgb2gray(img);
%     imgvec = double([r;g;b])';
      imgvec = img(:)';
     Xdata(index,:) = imgvec;

    ydata(index) = 1; % carre
    
    index = index +1;
end

disp('Coeur\n');
for i=1:124 % coeur

        outputString = sprintf('new_data/coeur/im_coeur (%d).jpg',i);
   
    img = imread(outputString);
    
%     r = img(:,:,1);
%     r = r(:);
%     
%     g = img(:,:,2);
%     g = g(:);
%     
%     b = img(:,:,3);
%     b = b(:);
    
    img = rgb2gray(img);
%     imgvec = double([r;g;b])';
    imgvec = img(:)';
   Xdata(index,:) = imgvec;

    ydata(index) = 2; % coeur
    
    index = index +1;
end

disp('Croix\n');
for i=1:297 % croix

    outputString = sprintf('new_data/croix/im (%d).jpg',i);
    img = imread(outputString);
    
%     r = img(:,:,1);
%     r = r(:);
%     
%     g = img(:,:,2);
%     g = g(:);
%     
%     b = img(:,:,3);
%     b = b(:);
    
    img = rgb2gray(img);
%     imgvec = double([r;g;b])';
    imgvec = img(:)';
     Xdata(index,:) = imgvec;

    ydata(index) = 3; % croix
    
    index = index +1;
end

disp('Rond\n');
for i=1:170 % rond

    outputString = sprintf('new_data/rond/im_rond (%d).jpg',i);
    img = imread(outputString);
    
%     r = img(:,:,1);
%     r = r(:);
%     
%     g = img(:,:,2);
%     g = g(:);
%     
%     b = img(:,:,3);
%     b = b(:);
    
    img = rgb2gray(img);
%     imgvec = double([r;g;b])';
    imgvec = img(:)';
     Xdata(index,:) = imgvec;

    ydata(index) = 4; % cube
    
    index = index +1;
end

disp('Triangle\n');
for i=1:322 % triangle
    
    outputString = sprintf('new_data/triangle/im_triangle (%d).jpg',i);
    img = imread(outputString);
    
%     r = img(:,:,1);
%     r = r(:);
%     
%     g = img(:,:,2);
%     g = g(:);
%     
%     b = img(:,:,3);
%     b = b(:);
    
    img = rgb2gray(img);
%     imgvec = double([r;g;b])';
    imgvec = img(:)';
     Xdata(index,:) = imgvec;

    ydata(index) = 5; % rond
    
    index = index +1;
end

disp('Fond\n');
for i=1:270 % fond
    
    outputString = sprintf('new_data/fond/im_fond (%d).jpg',i);
    img = imread(outputString);
    
%     r = img(:,:,1);
%     r = r(:);
%     
%     g = img(:,:,2);
%     g = g(:);
%     
%     b = img(:,:,3);
%     b = b(:);
    
    img = rgb2gray(img);
%     imgvec = double([r;g;b])';
    imgvec = img(:)';
     Xdata(index,:) = imgvec;

    ydata(index) = 6; % triangle
    
    index = index +1;
end




save('newdata_forme.mat', 'Xdata', 'ydata');