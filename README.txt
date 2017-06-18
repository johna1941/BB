A (very) basic basic Geant4 skeleton application

In this approach quantities of interest are specified in a file BBData.hh and initialised in BBData.cc. They are in a globally available namespace so that they may be accessed from anywhere, thus avoiding having to give one user action access to data members of another. However, multithreading complicates this a little and it's not clear that this is the simplest approach. Perhaps it's wiser to follow Geant4's basic examples.

In addition we use the General Particle Source.

Information is written to a comma-separated-values (CSV) file. whist.pl is a histogramming script:
cat outFile.csv | awk -F, '{print(1,$10)}' | whist.pl 0 1 100 >x.hist
Then in gnuplot:
gnuplot> plot "x.hist" with steps
