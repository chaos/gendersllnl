# Before `make install' is performed this script should be runnable with
# `make test'. After `make install' it should work as `perl test.pl'

#########################

# change 'tests => 1' to 'tests => last_test_to_print';

use Test;
BEGIN { plan tests => 1 };
use Libgendersllnl;
ok(1); # If we made it this far, we're ok.

#########################

# Insert your test code below, the Test module is use()ed here so read
# its man page ( perldoc Test ) for help writing this test script.

$handle = Libgendersllnl->genders_handle_create();
if (!defined($handle)) {
    print "Error, genders_handle_create()\n";
    exit(1);
}

$ret = $handle->genders_load_data();
if ($ret == -1) {
    print "Error, genders_load_data()\n";
    exit(1);
}

$nodename = $handle->genders_get_cluster("mdevi");
if (!defined($nodename)) {
    print "Error, genders_get_cluster()\n";
    exit(1);
}
print "Cluster is: ",$nodename,"\n\n"; 

$nodename = $handle->genders_get_cluster();
if (!defined($nodename)) {
    print "Error, genders_get_cluster()\n";
    exit(1);
}
print "Cluster is: ",$nodename,"\n\n"; 

$nodes = $handle->genders_getaltnodes();
if (!defined($nodes)) {
    print "Error, genders_getnodes()\n";
    exit(1);
}
foreach $_ (@$nodes) {
    print "node: ",$_,"\n";
}
print "\n";

$nodes = $handle->genders_getaltnodes("compute");
if (!defined($nodes)) {
    print "Error, genders_getnodes()\n";
    exit(1);
}
foreach $_ (@$nodes) {
    print "compute node: ",$_,"\n";
}
print "\n";

$nodes = $handle->genders_getaltnodes("resmgr", "both");
if (!defined($nodes)) {
    print "Error, genders_getnodes()\n";
    exit(1);
}
foreach $_ (@$nodes) {
    print "res=both node: ",$_,"\n";
}
print "\n";

$nodes = $handle->genders_getaltnodes_preserve();
if (!defined($nodes)) {
    print "Error, genders_getnodes()\n";
    exit(1);
}
foreach $_ (@$nodes) {
    print "p node: ",$_,"\n";
}
print "\n";

$nodes = $handle->genders_getaltnodes_preserve("compute");
if (!defined($nodes)) {
    print "Error, genders_getnodes()\n";
    exit(1);
}
foreach $_ (@$nodes) {
    print "p compute node: ",$_,"\n";
}
print "\n";

$nodes = $handle->genders_getaltnodes_preserve("resmgr", "both");
if (!defined($nodes)) {
    print "Error, genders_getnodes()\n";
    exit(1);
}
foreach $_ (@$nodes) {
    print "p res=both node: ",$_,"\n";
}
print "\n";

$ret = $handle->genders_isaltnode("mdevi");
print "mdevi - ",$ret,"\n";
$ret = $handle->genders_isaltnode("emdevi");
print "emdevi - ",$ret,"\n";
$ret = $handle->genders_isaltnode("foo");
print "foo - ",$ret,"\n";

$ret = $handle->genders_isnode_or_altnode("mdevi");
print "mdevi - ",$ret,"\n";
$ret = $handle->genders_isnode_or_altnode("emdevi");
print "emdevi - ",$ret,"\n";
$ret = $handle->genders_isnode_or_altnode("foo");
print "foo - ",$ret,"\n";

$ret = $handle->genders_to_gendname("mdevi");
print "mdevi - ",$ret,"\n";
$ret = $handle->genders_to_gendname("emdevi");
print "emdevi - ",$ret,"\n";
$ret = $handle->genders_to_gendname("foo");
print "foo - ",$ret,"\n";

$ret = $handle->genders_to_gendname_preserve("mdevi");
print "mdevi - ",$ret,"\n";
$ret = $handle->genders_to_gendname_preserve("emdevi");
print "emdevi - ",$ret,"\n";
$ret = $handle->genders_to_gendname_preserve("foo");
print "foo - ",$ret,"\n";

$ret = $handle->genders_to_altname("mdevi");
print "mdevi - ",$ret,"\n";
$ret = $handle->genders_to_altname("emdevi");
print "emdevi - ",$ret,"\n";
$ret = $handle->genders_to_altname("foo");
print "foo - ",$ret,"\n";

$ret = $handle->genders_to_altname_preserve("mdevi");
print "mdevi - ",$ret,"\n";
$ret = $handle->genders_to_altname_preserve("emdevi");
print "emdevi - ",$ret,"\n";
$ret = $handle->genders_to_altname_preserve("foo");
print "foo - ",$ret,"\n";



