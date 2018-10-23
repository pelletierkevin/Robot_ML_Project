clear all;
close all;
clc;

maxhigh = 0;
maxwidth = 0;

% for i=1:64
%     if(i < 10)
%         outputString = sprintf('image_000%d.jpg',i);
%     
%     else
%         outputString = sprintf('image_00%d.jpg',i);
%         
%     end
%     
%     colormap(gray)
%     A = imread(outputString);
%     if(size(A,3) > 1)
%         A = rgb2gray(A);
%     end
%     
%     imagesc(A);
%     
%     if(size(A,1) > maxhigh)
%         maxhigh = size(A,1);
%     end
%     
%     if(size(A,2) > maxwidth)
%         maxwidth = size(A,2);
%     end
%     
%     
%     
% end


for i=1:4
    

    outputString = sprintf('new_data/coeur/resize (%d).jpg',i);

    
%    colormap(gray)
    img = imread(outputString);
    
%     if(size(A,3) > 1)
%         A = rgb2gray(A);
%     end
    
    new_img = imresize(img, [168, 300]);
    

%    outputString = sprintf('imageres_neg_%d.jpg',i);
    

    imwrite(new_img, outputString);

    
end


