use ExtUtils::MakeMaker;
# See lib/ExtUtils/MakeMaker.pm for details of how to influence
# the contents of the Makefile that is written.
WriteMakefile(
    'NAME'		=> 'Gendersllnl',
    'VERSION_FROM'	=> 'Gendersllnl.pm',
    'PREREQ_PM'		=> {},
    ($] >= 5.005 ?
      (ABSTRACT_FROM => 'Gendersllnl.pm',
       AUTHOR     => 'Albert Chu <chu11@llnl.gov>') : ()),
);
