BB: a (very) basic basic Geant4 skeleton application

In this approach quantities of interest are distributed amongst the action classes as seems appropriate. If one class needs access to the data of another, its pointer is recovered from the run manager and the one has to be declared a friend. There are still some "global" quantities that are specified in BBData.hh and initialised in BBData.cc.

We use the General Particle Source.

Information is written to a comma-separated-values (CSV) file.

whist.pl is a histogramming script. It may be used as follows:
cat outFile.csv | awk -F, '{print(1,$10)}' | whist.pl 0 1 100 >x.hist
Then in gnuplot:
gnuplot> plot "x.hist" with steps
