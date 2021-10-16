#!/bin/sh

# Display usage
cpack_usage()
{
  cat <<EOF
Usage: $0 [options]
Options: [defaults in brackets after descriptions]
  --help            print this message
  --version         print cmake installer version
  --prefix=dir      directory in which to install
  --include-subdir  include the HelloWorld-1.6.1-Linux subdirectory
  --exclude-subdir  exclude the HelloWorld-1.6.1-Linux subdirectory
  --skip-license    accept license
EOF
  exit 1
}

cpack_echo_exit()
{
  echo $1
  exit 1
}

# Display version
cpack_version()
{
  echo "HelloWorld Installer Version: 1.6.1, Copyright (c) Humanity"
}

# Helper function to fix windows paths.
cpack_fix_slashes ()
{
  echo "$1" | sed 's/\\/\//g'
}

interactive=TRUE
cpack_skip_license=FALSE
cpack_include_subdir=""
for a in "$@"; do
  if echo $a | grep "^--prefix=" > /dev/null 2> /dev/null; then
    cpack_prefix_dir=`echo $a | sed "s/^--prefix=//"`
    cpack_prefix_dir=`cpack_fix_slashes "${cpack_prefix_dir}"`
  fi
  if echo $a | grep "^--help" > /dev/null 2> /dev/null; then
    cpack_usage
  fi
  if echo $a | grep "^--version" > /dev/null 2> /dev/null; then
    cpack_version
    exit 2
  fi
  if echo $a | grep "^--include-subdir" > /dev/null 2> /dev/null; then
    cpack_include_subdir=TRUE
  fi
  if echo $a | grep "^--exclude-subdir" > /dev/null 2> /dev/null; then
    cpack_include_subdir=FALSE
  fi
  if echo $a | grep "^--skip-license" > /dev/null 2> /dev/null; then
    cpack_skip_license=TRUE
  fi
done

if [ "x${cpack_include_subdir}x" != "xx" -o "x${cpack_skip_license}x" = "xTRUEx" ]
then
  interactive=FALSE
fi

cpack_version
echo "This is a self-extracting archive."
toplevel="`pwd`"
if [ "x${cpack_prefix_dir}x" != "xx" ]
then
  toplevel="${cpack_prefix_dir}"
fi

echo "The archive will be extracted to: ${toplevel}"

if [ "x${interactive}x" = "xTRUEx" ]
then
  echo ""
  echo "If you want to stop extracting, please press <ctrl-C>."

  if [ "x${cpack_skip_license}x" != "xTRUEx" ]
  then
    more << '____cpack__here_doc____'
   DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE
                   Version 2, December 2004

Copyright (C) 2004 Sam Hocevar <sam@hocevar.net>

Everyone is permitted to copy and distribute verbatim or modified
copies of this license document, and changing it is allowed as long
as the name is changed.

           DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE
  TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION

 0. You just DO WHAT THE FUCK YOU WANT TO.
 

____cpack__here_doc____
    echo
    while true
      do
        echo "Do you accept the license? [yn]: "
        read line leftover
        case ${line} in
          y* | Y*)
            cpack_license_accepted=TRUE
            break;;
          n* | N* | q* | Q* | e* | E*)
            echo "License not accepted. Exiting ..."
            exit 1;;
        esac
      done
  fi

  if [ "x${cpack_include_subdir}x" = "xx" ]
  then
    echo "By default the HelloWorld will be installed in:"
    echo "  \"${toplevel}/HelloWorld-1.6.1-Linux\""
    echo "Do you want to include the subdirectory HelloWorld-1.6.1-Linux?"
    echo "Saying no will install in: \"${toplevel}\" [Yn]: "
    read line leftover
    cpack_include_subdir=TRUE
    case ${line} in
      n* | N*)
        cpack_include_subdir=FALSE
    esac
  fi
fi

if [ "x${cpack_include_subdir}x" = "xTRUEx" ]
then
  toplevel="${toplevel}/HelloWorld-1.6.1-Linux"
  mkdir -p "${toplevel}"
fi
echo
echo "Using target directory: ${toplevel}"
echo "Extracting, please wait..."
echo ""

# take the archive portion of this file and pipe it to tar
# the NUMERIC parameter in this command should be one more
# than the number of lines in this header file
# there are tails which don't understand the "-n" argument, e.g. on SunOS
# OTOH there are tails which complain when not using the "-n" argument (e.g. GNU)
# so at first try to tail some file to see if tail fails if used with "-n"
# if so, don't use "-n"
use_new_tail_syntax="-n"
tail $use_new_tail_syntax +1 "$0" > /dev/null 2> /dev/null || use_new_tail_syntax=""

extractor="pax -r"
command -v pax > /dev/null 2> /dev/null || extractor="tar xf -"

tail $use_new_tail_syntax +164 "$0" | gunzip | (cd "${toplevel}" && ${extractor}) || cpack_echo_exit "Problem unpacking the HelloWorld-1.6.1-Linux"

echo "Unpacking finished successfully"

exit 0
#-----------------------------------------------------------
#      Start of TAR.GZ file
#-----------------------------------------------------------;
� �D`a �\}pŕ���VHZ��D�E��+�c���8���G�l�V�u3�vGҘ���X�l�pl焋T¥LUrw�
\]�ਊ�(��]��s|8�(D8K�☜/�������1��#w�.����{�_l�l�{;!������N���� K���[���֎_ ����|���1TrY%����de:#'���>���C�&eο %��L"~~�8����vt��o��hi��������q�X�������ͦ��%��5���O__��]�����*�;9���[oG�kph<O/Fjc���i�)��\�ӯ���������=v#e���44�~u) ��q��D/@��F�)O'��"vyʻ��9��#��FN(���0��I*x�U`�����*����Ҟ�<�FJ���	y����D�9!�r�ͳ]�m�l�ߢ���@�e�14o�s0~�՟����Ǿ�R	6����f���a#2��ӥD��V������nw����=�n�ƹ7��o�J���^���o��Y}�#U7�����o�l�x��㷏_��o~k��c��G��j�~�-��;
�-�P��㿰��������e�vS����oZ�[oa��B�n�g,�]����ca�a��[�{-�_g��j�����cğ��e&�*��|��`<d�m�O����j�q�~�_�������{����p�	�������9"��x��+���:�o%�v�O#�!v���fbg7�Co �Y%۰�@��锈.Q���f1.e�)9�H���}�tJ�N$$�μ榈���"J0��fD%��#Q�_xV�ND�rLLg��M���1�G6m�(�����-��SS��61�.��p��%�Nd�2�Bf���;t8��h�R��p�C�F�|��T_0<�)6�)�Jt��u��A�f�nx`$���a4ܳ�⌔ɦSф�̉w���Mݙv,���T|��������f=��|toH��|��9-���B+.ı�9G�l.)��]�p�ncӷ��Q9P�Q1�H��B�I۝pɉH���dTNQ�G�(\�7@4.��\V�C/��s�߄������5RP@��f)��es���<lX���V l��[�m�U��􍏇zŠ�U��ǡp��%Ȳ�#h�wK����s�U��i'���q����g'T������U!�nrcGR�z���N�k�.vhXn�\�v�ty�������m.�w3����#vt��$��~�y�����9�>?-������L��&?@��=F��ϓ�z�l�YP,G������������3���u~����K�EcY��tF��>N�T��3*�28��5�����w1�,��ϥ����`p7�/0x%�?��0��b��1x5�?��������A��_/��]�Ga�7na����J�oQ��G����p��~�O�W^I�:,��@N�������a����1X��J睘\�]�H�Wa~��W`�v�wc>�󕘿Q�/�|H�0��j�_��5�_My�����k��f����?���_��.�?�l����w8�ǿ��/q����3�?v����0�_+ãC�\�n$������h��#T9� �7���"לV����Z��t*���u���X"�?������g���p���ç��9��Y�����<����ȿ��߁�rƄ���y!B��v@�0xVUq8yϹvA9�6�k�{�DcP/W�x~�A!�;�:�l���"t�����#�7B�?���#�oC���Zc�Q�*R� ���v㮫��p9VB���A5�=b$��8��E������N��j�E�?=��xB��W�[,��i)܄�#���(�^��-��A�t�զHSB \ػ�Z��(}���C`��ћ������mX���y_�E��Hz���7o[� �ߛ��~>wz~���\˞]�U��z؟C�?�q�o��� ��^��m��,��n�H����cp��V�
�i���cao��`;Z�p�R!̇O�~��-M�k�݋7;�������� }e0�rhl0�^h4�L��|
��gОY8�G���3e]�U�ކ�'������
�u��K6��r�B����B_m��&�M����}X�y˥\ʥ\ʥ\ʥ\ʥ\>�b��`� �R&+�S>�'�OÛvLG_ԗ�f��\֗�����Lg >#e&���f�ə�件y�o=��wJ���O��t�nn��q�8�η��[U}҇WT���O!��w��@�<��N�����U�*H�;��C��B���aH������h+�)���Y����½@pS��v�;��
|�u�C��^��
<�O×k�v�w���\���+��/���M�r��G!���z��Cؓ�o��Z �?W�����n��
d������U�y�#k�����߿�q�{�^
���/f�q5�����a}+[�]�G�����(8���؀����AO��a�o�3�iz���	ܿJ�t�Wl���<]!O �i���z=�o�Ǎ�wB;M�{^����` �m�g��)[�;�����P˥\ʥ\ʥ\ʥ\ʥ\�c�q4���Q�q�,U��ч���'_h��$��b��8�F�8��D��u��4�ཱིj�G�4�3�@����@c	�yC�@(s�
���!q4fb�t�~Ϣ�4��x�?Pe����Ә��Z`������F����{*᩟+��7���!��b�?I�q�%8��B�	���Bw�@�B�$t�У�.�Bȧ�A�h���w��il"�Rr�k���@s�3���]-�m��(��a���xq#���ύ��4�]��7�L'�W�Pa���uc�+��f�/�׵��׿�6��x���5�_�>S�k�뀋�����M���3z<���M�z0m� ��g��̈7�~�p���/�#��bܮ����;~��8�>;� 7������ �w�6�p��*��t���2gg˗���?��/n���n��9F��N6��G�A��Az�B��f�Z��e6TW�&��L>�+]�}�Κ��j��4N��?�.����w'�K?�	l�t�}>�\�G��d�����`;���Y�x�������s�����fG_���i�ﵙ��G,���*NX�ן���8���<���#�	\����y -Ns�y�y>�>�y>Ă�<_�1����y�,�OZ��.�+]����V�y>Ĕ����~�����(Y%79鏁b^��$�ʟȢ���8�HODb\Ig�b47bi�fB����@G�\Ǥ��L&:'J)%3&3Ѥ$�s��Ta8�n-�F��fgq��P�Y�I;�$�ҩ������K�S[G�+r��Q@>��)1���qI�C|@���q���T�M��Z�~r.�#�Ł����ҏPč[�İ@@�u>�������3Ҥ�<���/��6�A���}�AC��F���o��G��P�PX,������Vy�$m���0f;�j�g��]��|�ԎRo�$�b�F���9Q�Ĺ��S:Vl"Oi-�H�j����p�d>�ia��L���¦�����=�sbJ?y==L���9Wf�!%�<61��+��S�ĭ;�,7�L6�D.c����K*�	H��F�镜�&g�?�V$�T*�ɤ�`)s4���f9N 8p�Jt
��hv��s)؄F��VC�v�e�D	�������3�.�Sir��b�?���#�Ϥ�>旦ɝb:�)r��XL�fcҌ"*xl��}S�A�a�Ѥ�k�~xK�;���#t΄e�y�U�=-6�Gon���oZ�����y�Wp����AN���h���
����i�O�(�������?
��3=��i��C�>=璁1כ�GP��;����v��}Q}znA� 翝�w�,M�ق*#] E�������U}��������G����%<=/�t�ѿ�D�qP���q#�稴����O�_(]�����x�ӧ�4:� �'��W���?���Ʉ�ǭޟC�>�~Li'Ϗ�O�q���a���������@X��*�Oϥ(]�>0|�'8}z~E�Ŝ<���o���a�W���?�n�:lZ�$է�M������6cn��;!�}ұ
N�����O��~�b���7،���]r L?��>-kɁ��>�o��܀�Yp9i�?��_�p��6vPZ�?CF�#�@��S��Ζ��4��ˈ��g����_��U��_.�R.��I���9 P  