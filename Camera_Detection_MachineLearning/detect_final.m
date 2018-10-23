function [result,p] = detect_final()    
    
    clear all;
    close all;
    clc;

    % definition couleur en degré
    orange = 30; %1
    jaune = 60; %2
    vert = 110; %3
    bleu = 200; %4  
    violet = 270; %5
    rose = 300; %6

    height_img = 168; % hauteur de l'image
    width_img = 300; % largeur de l'image

    load('weights_gray.mat');
    path = sprintf('im.jpg');

    img = imread(path); % recupere l'image
    img = imresize(img, [height_img, width_img]);
    img_hsv = rgb2hsv(img);
    img_hsv(:,:,1) = img_hsv(:,:,1)*360; % passe directement valeur couleur en degre 
    figure(1);
    imagesc(img_hsv);
    figure(2);
    imagesc(img);


    %% DETECTION COULEUR
    nb_valides = 0; %nb de pixels représentant une couleur (pour chaque colonne)
    pixel_color = 0; % valeur couleur du HSV de 0 à 360 ° 
    pixel_bright = 0; % valeur brillance du pixel de 0 à 1
    index_spec = 1;
    color_found = 0;
    for colonnes=1:width_img % Parcours chaque pixel de l'image

        for lignes=1:height_img

            pixel_value = img_hsv(lignes,colonnes,:);
            if(pixel_value(2) > 0.45 && pixel_value(3) > 0.3 && pixel_value(1) > 0.03) %% ne correspond pas a blanc/noir/gris

                if(pixel_value(1) < (orange+15) && pixel_value(1) > (orange-15) ) %% filtrage pour les couleurs qui tendent vers orange/beige très presente pour eviter false positive

                        if(pixel_value(2) > 0.6 && pixel_value(3) > 0.67) %% le orange qu'on souhaite a une luminosité forte (pas du beige)
                            pixel_color = pixel_color + pixel_value(1);
                            pixel_bright = pixel_bright + pixel_value(3);
                            nb_valides = nb_valides +1;
                        end
                else % toutes les autres couleurs
                    pixel_color = pixel_color + pixel_value(1); % valeur de la couleur du cercle chromatique
                    pixel_bright = pixel_bright + pixel_value(3); % brillance de la couleur
                    nb_valides = nb_valides +1;
                end


            end

        end
        if(nb_valides > 30)
            color_mean(index_spec) = (pixel_color/nb_valides);
            bright_mean(index_spec) = (pixel_bright/nb_valides);
            index_spec = index_spec +1;
            color_found = 1; % si pas de couleur trouve, color_mean n'est pas definit et bloque le prgm
        end

        nb_valides = 0; % on remet a zero
        pixel_color = 0;
        pixel_bright = 0;

    end



    if(color_found == 1) % on rentre dans le traitement seulement si des couleurs ont été trouvés

        hsv_mean = mean(color_mean);
        length = size(color_mean,2);

        for i=1:length

                    if( color_mean(i) < (orange+15) && color_mean(i) > (orange-15) )
                        couleur(i) = 1;

                    elseif( color_mean(i) < (jaune+15) && color_mean(i) > (jaune-15) )
                        couleur(i) = 2;

                    elseif( color_mean(i) < (vert+45) && color_mean(i) > (vert-35) )
                        couleur(i) = 3;

                    elseif( color_mean(i) < (bleu+45) && color_mean(i) > (bleu-45) )
                        couleur(i) = 4;

                    elseif( color_mean(i) < (violet+35) && color_mean(i) > (violet-25) )
                        couleur(i) = 5;

                    elseif( color_mean(i) <= (rose+55) && color_mean(i) > (rose+5) )
                        if(bright_mean(i) >= 0.8) % brillance supérieur a un certain seuil
                            couleur(i) = 6; %rose
                        else
                            couleur(i) = 5; % violet qui correspond au rose foncé
                        end

                    elseif( color_mean(i) <= 15 || color_mean(i) > 355 )
                        couleur(i) = 7; 

                    end   

        end

        for i=1:7
                nb_out(i) = sum(couleur==i);
        end

        result = find(nb_out==max(nb_out(:)));


    else  % si pas de couleur trouvee
        result = 0; % pas de couleur trouvee  
    end

    for(i=1:size(result,2) ) %boucle for au cas ou 2(ou+) couleur max ont le meme nb de detections

        if(result(i) == 1)
            disp('Orange');
        elseif(result(i) == 2)
            disp('Jaune');
        elseif (result(i) == 3)    
            disp('Vert');
        elseif (result(i) == 4)    
            disp('Bleu');
        elseif(result(i) == 5)
            disp('Violet');
        elseif (result(i) == 6)    
            disp('Rose');
        elseif (result(i) == 7)    
            disp('Rouge');   
        elseif (result(i) == 7)    
            disp('Rouge');  
        elseif (result(i) == 0)    
            disp('Pas de couleur');
        end  

    end

    %% DETECTION FORME

    img = imresize(img, [168 300] );
    img = double(rgb2gray(img));
    imgvec = img(:)';
    imgvec = (imgvec-mean(imgvec))/255;

    [p, coef_sorties] = predict(Theta1, Theta2, imgvec);


    if(p == 1)
        disp('Carre');
    elseif(p == 2)
        disp('Coeur');
    elseif (p == 3)    
        disp('Croix');
    elseif (p == 4)    
        disp('Rond');
    elseif(p == 5)
        disp('Triangle');
    elseif (p == 6)    
        disp('Fond');

    end

    coef_sorties


end