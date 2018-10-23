clear all;
close all;
clc;

% Soccer ball detection



input_layer_size  = 151200;  % 90x90 Input Images of Digits
hidden_layer_size = 80;   %  hidden units
output_layer_size = 3;
num_labels = 1; 

y = ones(1613,1);
load('regDataset.mat');
X = double(Xdata);
y = ydata;
Theta1 = randInitializeWeights(input_layer_size,hidden_layer_size);
Theta2 = randInitializeWeights(hidden_layer_size,output_layer_size);
lambda = 1;
initial_nn_params = [Theta1(:) ; Theta2(:)];

J = nnCostFunction(initial_nn_params, input_layer_size, hidden_layer_size, ...
                   num_labels, X, y, lambda);
               
               
options = optimset('MaxIter', 60);

costFunction = @(p) nnCostFunction(p, ...
                                   input_layer_size, ...
                                   hidden_layer_size, ...
                                   num_labels, X, y, lambda);
                               
[nn_params, cost] = fmincg(costFunction, initial_nn_params, options);

Theta1 = reshape(nn_params(1:hidden_layer_size * (input_layer_size + 1)), ...
                 hidden_layer_size, (input_layer_size + 1));

Theta2 = reshape(nn_params((1 + (hidden_layer_size * (input_layer_size + 1))):end), ...
                 num_labels, (hidden_layer_size + 1));

             
  result = predict(Theta1, Theta2, X);        
  efficiency = 100*sum(result==y)/153          
  



