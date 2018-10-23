clear all;
close all;
clc;

maxhigh = 0;
maxwidth = 0;

for i=1:64
    if(i < 10)
        outputString = sprintf('image_000%d.jpg',i);
    
    else
        outputString = sprintf('image_00%d.jpg',i);
        
    end
    
    colormap(gray)
    A = imread(outputString);
    if(size(A,3) > 1)
        A = rgb2gray(A);
    end
    
    imagesc(A);
    
    if(size(A,1) > maxhigh)
        maxhigh = size(A,1);
    end
    
    if(size(A,2) > maxwidth)
        maxwidth = size(A,2);
    end
    
    
    
end


for i=1:64
    
    if(i < 10)
        outputString = sprintf('image_000%d.jpg',i);
    
    else
        outputString = sprintf('image_00%d.jpg',i);
        
    end
    
    colormap(gray)
    A = imread(outputString);
    
    if(size(A,3) > 1)
        A = rgb2gray(A);
    end
    
    newA = imresize(A, [maxhigh, maxwidth]);
    imagesc(newA);
    
    if(i < 10)
        outputString = sprintf('imageresh_000%d.jpg',i);
    
    else
        outputString = sprintf('imageresh_00%d.jpg',i);
        
    end
    imwrite(newA, outputString);
    
    
    pause(0.1);
    
end


