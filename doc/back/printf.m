
     NAME
          printf, fprintf, sprintf - print formatted output

     SYNTAX
          #include <stdio.h>

          int printf (format [ , arg ] ...  )
          char *format;

          int fprintf (stream, format [ , arg ] ...  )
          FILE *stream;
          char *format;

          int sprintf (s, format [ , arg ] ...  )
          char *s, format;

     DESCRIPTION
          Printf places output on the standard output stream stdout.
          Fprintf places output on the named output stream.  Sprintf
          places ``output,'' followed by the null character (\0), in
          consecutive bytes starting at *s; it is the user's
          responsibility to ensure that enough storage is available.
          Each function returns the number of characters transmitted
          (not including the \0 in the case of sprintf), or a negative
          value if an output error was encountered.

          Each of these functions converts, formats, and prints its
          args under control of the format.  The format is a character
          string that contains two types of objects: plain characters,
          which are simply copied to the output stream, and conversion
          specifications, each of which results in fetching of zero or
          more args.  The results are undefined if there are
          insufficient args for the format.  If the format is
          exhausted while args remain, the excess args are simply
          ignored.

          Each conversion specification is introduced by the character
          %.  After the %, the following appear in sequence:

               Zero or more flags, which modify the meaning of the
               conversion specification.

               An optional decimal digit string specifying a minimum
               field width.  If the converted value has fewer
               characters than the field width, it will be padded on
               the left (or right, if the left-adjustment flag `-',
               described below, has been given) to the field width.
               If the field width for an s conversion is preceded by a
               0, the string is right adjusted with zero-padding on
               the left.

               A precision that gives the minimum number of digits to
               appear for the d, o, u, x, or X conversions, the number
               of digits to appear after the decimal point for the e
               and f conversions, the maximum number of significant
               digits for the g conversion, or the maximum number of
               characters to be printed from a string in s conversion.
               The precision takes the form of a period (.) followed
               by a decimal digit string; a null digit string is
               treated as zero.

               An optional l (ell) specifying that a following d, o,
               u, x, or X conversion character applies to a long
               integer arg.  A l before any other conversion character
               is ignored.

               A character that indicates the type of conversion to be
               applied.

          A field width or precision may be indicated by an asterisk
          (*) instead of a digit string.  In this case, an integer arg
          supplies the field width or precision.  The arg that is
          actually converted is not fetched until the conversion
          letter is seen, so the args specifying field width or
          precision must appear before the arg (if any) to be
          converted.

          The flag characters and their meanings are:
          -         The result of the conversion will be left-
                    justified within the field.
          +         The result of a signed conversion will always
                    begin with a sign (+ or -).
          blank     If the first character of a signed conversion is
                    not a sign, a blank will be prefixed to the
                    result.  This implies that if the blank and +
                    flags both appear, the blank flag will be ignored.
          #         This flag specifies that the value is to be
                    converted to an ``alternate form.''  For c, d, s,
                    and u conversions, the flag has no effect.  For o
                    conversion, it increases the precision to force
                    the first digit of the result to be a zero.  For x
                    or X conversion, a non-zero result will have 0x or
                    0X prefixed to it.  For e, E, f, g, and G
                    conversions, the result will always contain a
                    decimal point, even if no digits follow the point
                    (normally, a decimal point appears in the result
                    of these conversions only if a digit follows it).
                    For g and G conversions, trailing zeroes will not
                    be removed from the result (which they normally
                    are).

          The conversion characters and their meanings are:

          d,o,u,x,X The integer arg is converted to signed decimal,
                    unsigned octal, decimal, or hexadecimal notation
                    (x and X), respectively; the letters abcdef are
                    used for x conversion and the letters ABCDEF for X
                    conversion.  The precision specifies the minimum
                    number of digits to appear; if the value being
                    converted can be represented in fewer digits, it
                    will be expanded with leading zeroes.  (For
                    compatibility with older versions, padding with
                    leading zeroes may alternatively be specified by
                    prepending a zero to the field width.  This does
                    not imply an octal value for the field width.) The
                    default precision is 1.  The result of converting
                    a zero value with a precision of zero is a null
                    string.
          f         The float or double arg is converted to decimal
                    notation in the style ``[-]ddd.ddd,'' where the
                    number of digits after the decimal point is equal
                    to the precision specification.  If the precision
                    is missing, six digits are output; if the
                    precision is explicitly 0, no decimal point
                    appears.
          e,E       The float or double arg is converted in the style
                    ``[-]d.ddde+dd,'' where there is one digit before
                    the decimal point and the number of digits after
                    it is equal to the precision; when the precision
                    is missing, six digits are produced; if the
                    precision is zero, no decimal point appears.  The
                    E format code will produce a number with E instead
                    of e introducing the exponent.  The exponent
                    always contains at least two digits.
          g,G       The float or double arg is printed in style f or e
                    (or in style E in the case of a G format code),
                    with the precision specifying the number of
                    significant digits.  The style used depends on the
                    value converted: style e will be used only if the
                    exponent resulting from the conversion is less
                    than -4 or greater than the precision.  Trailing
                    zeroes are removed from the result; a decimal
                    point appears only if it is followed by a digit.
          c         The character arg is printed.
          s         The arg is taken to be a string (character
                    pointer) and characters from the string are
                    printed until a null character (\0) is encountered
                    or the number of characters indicated by the
                    precision specification is reached.  If the
                    precision is missing, it is taken to be infinite,
                    so all characters up to the first null character
                    are printed.  A NULL value for arg will yield
                    undefined results.
          %         Print a %; no argument is converted.

          In no case does a non-existent or small field width cause
          truncation of a field; if the result of a conversion is
          wider than the field width, the field is simply expanded to
          contain the conversion result.  Characters generated by
          printf and fprintf are printed as if putc() had been
          called.

     EXAMPLES
          To print a date and time in the form ``Sunday, July 3,
          10:02,'' where weekday and month are pointers to null-
          terminated strings:

               printf("%s, %s %d, %d:%.2d", weekday, month, day, hour, min);

          To print pi to 5 decimal places:

               printf("pi = %.5f", 4 * atan(1.0));

     SEE ALSO
          ecvt.m, putc.m, scanf.m, stdio.m

          (printed 07/30/92 - J B Systems)

