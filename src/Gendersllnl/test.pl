#!/usr/bin/perl -w
use Gendersllnl;

print $Genders::GENDERS_DEFAULT_FILE,"\n";

$handle = Gendersllnl->new();
if (!defined($handle)) {
    print "Error, genders_handle_create()\n";
    exit(1);
}

$nodename = $handle->getnodename();
print "Nodename is: ",$nodename,"\n\n"; 

$nodename = $handle->get_cluster("mdevi");
print "Cluster is: ",$nodename,"\n\n"; 

$nodename = $handle->get_cluster();
print "Cluster is: ",$nodename,"\n\n"; 

@nodes = $handle->getaltnodes();
foreach $_ (@nodes) {
    print "node: ",$_,"\n";
}
print "\n";

@nodes = $handle->getaltnodes("compute");
foreach $_ (@nodes) {
    print "compute node: ",$_,"\n";
}
print "\n";

@nodes = $handle->getaltnodes("resmgr", "both");
foreach $_ (@nodes) {
    print "res=both node: ",$_,"\n";
}
print "\n";

@nodes = $handle->getaltnodes_preserve();
foreach $_ (@nodes) {
    print "p node: ",$_,"\n";
}
print "\n";

@nodes = $handle->getaltnodes_preserve("compute");
foreach $_ (@nodes) {
    print "p compute node: ",$_,"\n";
}
print "\n";

@nodes = $handle->getaltnodes_preserve("resmgr", "both");
foreach $_ (@nodes) {
    print "p res=both node: ",$_,"\n";
}
print "\n";

$ret = $handle->isaltnode("mdevi");
print "mdevi - ",$ret,"\n";
$ret = $handle->isaltnode("emdevi");
print "emdevi - ",$ret,"\n";
$ret = $handle->isaltnode("foo");
print "foo - ",$ret,"\n";

$ret = $handle->isnode_or_altnode("mdevi");
print "mdevi - ",$ret,"\n";
$ret = $handle->isnode_or_altnode("emdevi");
print "emdevi - ",$ret,"\n";
$ret = $handle->isnode_or_altnode("foo");
print "foo - ",$ret,"\n";

$ret = $handle->to_gendname("mdevi");
print "mdevi - ",$ret,"\n";
$ret = $handle->to_gendname("emdevi");
print "emdevi - ",$ret,"\n";
$ret = $handle->to_gendname("foo");
print "foo - ",$ret,"\n";

$ret = $handle->to_gendname_preserve("mdevi");
print "mdevi - ",$ret,"\n";
$ret = $handle->to_gendname_preserve("emdevi");
print "emdevi - ",$ret,"\n";
$ret = $handle->to_gendname_preserve("foo");
print "foo - ",$ret,"\n";

$ret = $handle->to_altname("mdevi");
print "mdevi - ",$ret,"\n";
$ret = $handle->to_altname("emdevi");
print "emdevi - ",$ret,"\n";
$ret = $handle->to_altname("foo");
print "foo - ",$ret,"\n";

$ret = $handle->to_altname_preserve("mdevi");
print "mdevi - ",$ret,"\n";
$ret = $handle->to_altname_preserve("emdevi");
print "emdevi - ",$ret,"\n";
$ret = $handle->to_altname_preserve("foo");
print "foo - ",$ret,"\n";



