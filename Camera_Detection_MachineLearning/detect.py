import matlab.engine

eng= matlab.engine.start_matlab()
#eng.edit('detect_final', nargout=2)
couleur=0
forme=0
(couleur,forme) = eng.detect_final(nargout=2)
print(couleur,forme)
