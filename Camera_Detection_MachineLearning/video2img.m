clear all;
close all;
clc;


j=1;
nb_videos = 1;
index = 51;

for j=1:nb_videos

i = 1;
titre_video = sprintf('new_data/vid_rose_coeur.mp4');
video = VideoReader(titre_video);

while(hasFrame(video))
    img = readFrame(video);
    output = sprintf('new_data/coeur/im_coeur_%d.jpg',index);
    %img = imrotate(img, 180);
    if(mod(i,7) == 0)
        img = imresize(img, [168 300] );
        imwrite(img, output);
        index = index+1;
    end 
    i = i+1;
end

end