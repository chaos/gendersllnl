;#############################################################################
# $Id: Gendersllnl.pm,v 1.14 2003-08-14 23:56:42 achu Exp $
# $Source: /g/g0/achu/temp/genders-cvsbackup-full/gendersllnl/src/Gendersllnl/Gendersllnl.pm,v $
#############################################################################

package Gendersllnl;

use strict;
use Genders;
use Libgendersllnl;
our $VERSION = "2.0";

our @ISA = qw(Genders);

# need to bless into Libgendersllnl, therefore cannot use Genders' new.
sub new {
    my $proto = shift;
    my $class = ref($proto) || $proto;
    my $filename = shift;
    my $self = {};
    my $handle;
    my $ret;
    
    $self->{$debugkey} = 0;
    
    $handle = Libgendersllnl->genders_handle_create();
    if (!defined($handle)) {
        _errormsg($self, "genders_handle_create()");
        return undef;
    }

    $self->{$handlekey} = $handle;

    $ret = $self->{$handlekey}->genders_load_data($filename);
    if ($ret == -1) {
        _errormsg($self, "genders_load_data()");
        Libgenders::genders_handle_destroy($handle);
        return undef;
    } 

    bless ($self, $class);
    return $self;
}

sub get_cluster {
    my $self = shift;
    my $node = shift;
    my $cluster;

    if (ref($self)) {
        $cluster = $self->{$handlekey}->genders_get_cluster($node);
        if (!defined($cluster)) {
            _errormsg($self, "genders_get_cluster()");
            return "";
        }
        return $cluster;
    }
    else {
        return "";
    }
}

sub getaltnodes {
    my $self = shift;
    my $attr = shift;
    my $val = shift;
    my $altnodes;

    if (ref($self)) {
        $altnodes = $self->{$handlekey}->genders_getaltnodes($attr, $val);
        if (!defined($altnodes)) {
            _errormsg($self, "genders_getaltnodes()");
            return ();
        }
        return @$altnodes;
    }
    else {
        return ();
    }
}

sub getaltnodes_preserve {
    my $self = shift;
    my $attr = shift;
    my $val = shift;
    my $altnodes;

    if (ref($self)) {
        $altnodes = $self->{$handlekey}->genders_getaltnodes_preserve($attr, 
                                                                      $val);
        if (!defined($altnodes)) {
            _errormsg($self, "genders_getaltnodes_preserve()");
            return ();
        }
        
        return @$altnodes;
    }
    else {
        return ();
    }
}

sub isaltnode {
    my $self = shift;
    my $node = shift;
    my $retval;

    if (ref($self)) {
        $retval = $self->{$handlekey}->genders_isaltnode($node);
        if ($retval == -1) {
            _errormsg($self, "genders_isaltnode()");
            return 0;
        }
        return $retval; 
    }
    else {
        return 0;
    }
}

sub isnode_or_altnode {
    my $self = shift;
    my $node = shift;
    my $retval;

    if (ref($self)) {
        $retval = $self->{$handlekey}->genders_isnode_or_altnode($node);
        if ($retval == -1) {
            _errormsg($self, "genders_isnode_or_altnode()");
            return 0;
        }
        return $retval; 
    }
    else {
        return 0;
    }
}

sub to_gendname {
    my $self = shift;
    my $altnode = shift;
    my $gendname;

    if (ref($self)) {
        $gendname = $self->{$handlekey}->genders_to_gendname($altnode);
        if (!defined $gendname) {
            _errormsg($self, "genders_to_gendname()");
            return "";
        }
        return $gendname; 
    }
    else {
        return "";
    }
}

sub to_gendname_preserve {
    my $self = shift;
    my $altnode = shift;
    my $gendname;

    if (ref($self)) {
        $gendname = $self->{$handlekey}->genders_to_gendname_preserve($altnode);
        if (!defined $gendname) {
            _errormsg($self, "genders_to_gendname_preserve()");
            return "";
        }
        return $gendname; 
    }
    else {
        return "";
    }
}

sub to_altname {
    my $self = shift;
    my $node = shift;
    my $altname;

    if (ref($self)) {
        $altname = $self->{$handlekey}->genders_to_altname($node);
        if (!defined $altname) {
            _errormsg($self, "genders_to_altname()");
            return "";
        }
        return $altname; 
    }
    else {
        return "";
    }
}

sub to_altname_preserve {
    my $self = shift;
    my $node = shift;
    my $altname;

    if (ref($self)) {
        $altname = $self->{$handlekey}->genders_to_altname_preserve($node);
        if (!defined $altname) {
            _errormsg($self, "genders_to_altname_preserve()");
            return "";
        }
        return $altname; 
    }
    else {
        return "";
    }
}

sub to_gendnames {
    my $self = shift;
    my @altnames = @_;
    my @gendnames = ();
    my $gendname;

    if (ref($self)) {
        foreach (@altnames) {
            $gendname = $self->{$handlekey}->genders_to_gendname($_);
            if (!defined $gendname) {
                _errormsg($self, "genders_to_gendname()");
                return ();
            }
            push(@gendnames, $gendname);
        }
        return @gendnames;
    }
    else {
        return ();
    }
}

sub to_gendnames_preserve {
    my $self = shift;
    my @altnames = @_;
    my @gendnames = ();
    my $gendname;

    if (ref($self)) {
        foreach (@altnames) {
            $gendname = $self->{$handlekey}->genders_to_gendname_preserve($_);
            if (!defined $gendname) {
                _errormsg($self, "genders_to_gendname_preserve()");
                return ();
            }
            push(@gendnames, $gendname);
        }
        return @gendnames;
    }
    else {
        return ();
    }
}

sub to_altnames {
    my $self = shift;
    my @nodes = @_;
    my @altnames = ();
    my $altname;

    if (ref($self)) {
        foreach (@nodes) {
            $altname = $self->{$handlekey}->genders_to_altname($_);
            if (!defined $altname) {
                _errormsg($self, "genders_to_altname()");
                return ();
            }
            push(@altnames, $altname);
        }
        return @altnames; 
    }
    else {
        return ();
    }
}

sub to_altnames_preserve {
    my $self = shift;
    my @nodes = @_;
    my @altnames = ();
    my $altname;

    if (ref($self)) {
        foreach (@nodes) {
            $altname = $self->{$handlekey}->genders_to_altname_preserve($_);
            if (!defined $altname) {
                _errormsg($self, "genders_to_altname_preserve()");
                return ();
            }
            push(@altnames, $altname);
        }
        return @altnames; 
    }
    else {
        return ();
    }
}



1;

__END__

=head1 NAME

Gendersllnl - LLNL site specific Perl library for querying genders file

=head1 SYNOPSIS

 use Gendersllnl;

 $obj = Gendersllnl->new([$filename])

 $obj->get_cluster([$node])

 $obj->getaltnodes([$attr, [$val]])
 $obj->getaltnodes_preserve([$attr, [$val]])

 $obj->isaltnode($altnode)
 $obj->isnode_altnode($node)

 $obj->to_gendname($altnode)
 $obj->to_gendname_preserve($altnode)
 $obj->to_altname($node)
 $obj->to_altname_preserve($node)

 $obj->to_gendnames(@altnodes)
 $obj->to_gendnames_preserve(@altnodes)
 $obj->to_altnames(@nodes)
 $obj->to_altnames_preserve(@nodes)

=head1 DESCRIPTION

This package provides a LLNL site specific perl interface for querying
a genders file.  This package inherits from the Genders package, so
all Genders functionality is also included in this package.

=over 4

=item B<Gendersllnl-E<gt>new([$filename])>

Creates a Gendersllnl object and load genders data from the specified
file.  If the genders file is not specified, the default genders file
will be used.  Returns undef if file cannot be read.

=item B<$obj-E<gt>get_cluster([$node])>

Returns the name of the specified node's cluster.  If a node is not
specified, the current node is assumed.

=item B<$obj-E<gt>getaltnodes([$attr, [$val]])>

Returns a list of alternate named nodes with the specified attribute
and value.  If a value is not specified only the attribute is
considered.  If the attribute is not specified, the alternate names of
all nodes listed in the genders file are returned.  If any node does
not have an alternate name listed, this will return an empty list.

=item B<$obj-E<gt>getaltnodes_preserve([$attr, [$val]])>

Returns a list of alternate named nodes with the specified attribute
and value.  If a value is not specified only the attribute is
considered.  If the attribute is not specified, the alternate names of
all nodes listed in the genders file are returned.  If any node does
not have an alternate name listed, the genders nodename will be returned
in the list instead.

=item B<$obj-E<gt>isaltnode($altnode)>

Returns 1 if the specified alternate node name is listed in the
genders file, 0 if it is not.

=item B<$obj-E<gt>isnode_altnode($node)>

Returns 1 if the specified node name is listed in the genders file as
a genders node or an alternate node name, 0 if it is not.

=item B<$obj-E<gt>to_gendname($altnode)>

Returns the genders node name of the specified alternate node name.
Returns an empty string if the alternate node name is not found in 
the genders file.

=item B<$obj-E<gt>to_gendname_preserve($altnode)>

Returns the genders node name of the specified alternate node name.
Returns the specified alternate node name if it is not found in the
genders file.

=item B<$obj-E<gt>to_altname($node)>

Returns the alternate node name of the specified genders node name.
Returns an empty string if the genders node name is not found in 
the genders file.

=item B<$obj-E<gt>to_altname_preserve($node)>

Returns the alternate node name of the specified genders node name.
Returns the specified genders node name if it is not found in the
genders file.

=item B<$obj-E<gt>to_gendnames(@altnodes)>

Returns a list of genders node names for each alternate node name
listed in the specified list.  Returns an empty list if any alternate
node name is not found in the genders file.

=item B<$obj-E<gt>to_gendnames_preserve(@altnodes)>

Returns a list of genders node names for each alternate node name
listed in the specified list.  Preserves the alternate node name if it
is not found in the genders file.

=item B<$obj-E<gt>to_altnames(@nodes)>

Returns a list of alternate node names for each genders node name
listed in the specified list.  Returns an empty list if any genders
node name is not found in the genders file.

=item B<$obj-E<gt>to_altnames_preserve(@nodes)>

Returns a list of alternate node names for each genders node name
listed in the specified list.  Preserves the genders node name if it
is not found in the genders file.

=back 

=head1 AUTHOR

Albert Chu E<lt>chu11@llnl.govE<gt>

=head1 SEE ALSO

L<Libgenders>.

L<libgenders>.
