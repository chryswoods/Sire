"""
Fixed and improved version based on "extracting from C++ doxygen documented file Author G.D." and py++ code.

Distributed under the Boost Software License, Version 1.0. (See
accompanying file LICENSE_1_0.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
"""
from functools import reduce
import sys

try:
    from fuzzywuzzy import fuzz
except:
    print("please run sire.app/bin/pip install fuzzywuzzy")
    sys.exit(-1)

class doxygen_doc_extractor:
    """
    Extracts Doxygen styled documentation from source or generates it from description.
    """
    def __init__(self, doc_db={}):
        #for caching source
        self.file_name = None
        self.source = None
        self.db = doc_db
    #__init__

    def __call__(self, declaration):
        doc_lines = None
        try:
            if self.file_name != declaration.location.file_name:
                self.file_name = declaration.location.file_name
                self.source = open(declaration.location.file_name).readlines()

            find_block_end = False
            doc_lines = []
            for lcount in range(declaration.location.line-2, -1, -1):
                line = self.source[lcount]
                if not find_block_end:
                    try:
                        if line.rstrip()[-2:] == "*/":
                            find_block_end = True
                    except:
                        pass
                if find_block_end:
                    try:
                        if line.lstrip()[:2] == "/*":
                            find_block_end = False
                    except:
                        pass
                try:
                    final_str = self.clear_str(line) + "\n"
                except Exception as e:
                    final_str = line

                if not find_block_end and self.is_code(line):
                    break
                if final_str:
                    doc_lines.insert(0, final_str)
        except:
            pass
        finally:
            if doc_lines:
                final_doc_lines = [ line.replace("\n","\\n") for line in doc_lines[:-1] ]
                final_doc_lines.append(doc_lines[-1].replace("\n",""))
                return '\"' + ''.join(final_doc_lines) + '\"'
            else:
                # no documentation in the header file - did we find some in the
                # source files?
                cls = declaration.parent.name
                func = declaration.name

                try:
                    nargs = len(declaration.arguments)
                    data = self.db[cls][func][nargs]
                    docs = ""

                    if nargs == 0:
                        docs = self.clear_str(data[0][1])
                    elif len(data) == 1:
                        # there is only one choice, so use that
                        docs = self.clear_str(data[0][1])
                    else:
                        # we have a choice of documentation - match on
                        # the argument types
                        args = declaration.arguments
                        topscore = None
                        topmatch = None

                        for match in data:
                            score = 0
                            for i in range(0,len(args)):
                                score += fuzz.ratio(str(args[i]), match[0][i])

                            if topscore is None:
                                topmatch = match
                                topscore = score
                            elif score > topscore:
                                topmatch = match
                                topscore = score

                        if topscore:
                            docs = self.clear_str(topmatch[1])

                    return "\"%s\"" % docs
                except Exception as e:
                    return '\"\"'
    #__call__()

    def clear_str(self, tmp_str):
        """
        Replace */! by space and \brief, @fn, \param, etc
        """

        lines = tmp_str.split("\n")
        l2 = []
        for line in lines:
            line = line.lstrip().rstrip()
            if len(line) > 0:
                l2.append(line)

        tmp_str = "\\n".join(l2)

        clean = lambda tmp_str, sym, change2 = '': tmp_str.replace(sym, change2)

        tmp_str = reduce(clean, [tmp_str, '/','*','!',"\\brief","@brief","\\fn","@fn","\\ref","@ref", "\"", "\'", "\\c"])

        #commands list taken form : http://www.stack.nl/~dimitri/doxygen/commands.html
        replacement_list = [
#           "a",
            "addindex",
            "addtogroup",
            "anchor",
            "arg",
            "attention",
            "author",
#           "b",
#           "brief",
            "bug",
#           "c",
            "callgraph",
            "callergraph",
            "category",
            "class",
            ("code","[Code]"),
            "cond",
            "copybrief",
            "copydetails",
            "copydoc",
            "date",
            "def",
            "defgroup",
            "deprecated",
            "details",
            "dir",
            "dontinclude",
            ("dot","[Dot]"),
            "dotfile",
            "e",
            "else",
            "elseif",
            "em",
            ("endcode","[/Code]"),
            "endcond",
            ("enddot","[/Dot]"),
            "endhtmlonly",
            "endif",
            "endlatexonly",
            "endlink",
            "endmanonly",
            "endmsc",
            "endverbatim",
            "endxmlonly",
            "enum",
            "example",
            "exception",
            "extends",
            "f$",
            "f[",
            "f]",
            "f{",
            "f}",
            "file",
#           "fn",
            "headerfile",
            "hideinitializer",
            "htmlinclude",
            "htmlonly",
            "if",
            "ifnot",
            "image",
            "implements",
            "include",
            "includelineno",
            "ingroup",
            "internal",
            "invariant",
            "interface",
            "latexonly",
            "li",
            "line",
            "link",
            "mainpage",
            "manonly",
            "memberof",
            "msc",
#           "n",
            "name",
            "namespace",
            "nosubgrouping",
            "note",
            "overload",
#           "p",
            "package",
            "page",
            "par",
            "paragraph",
            "param",
            "post",
            "pre",
#           "private (PHP only)",
#           "privatesection (PHP only)",
            "property",
#           "protected (PHP only)",
#           "protectedsection (PHP only)",
            "protocol",
#           "public (PHP only)",
#           "publicsection (PHP only)",
#           "ref",
            "relates",
            "relatesalso",
            "remarks",
            "return",
            "retval",
            "sa",
            "section",
            "see",
            "showinitializer",
            "since",
            "skip",
            "skipline",
            "struct",
            "subpage",
            "subsection",
            "subsubsection",
            "test",
            "throw",
            ("todo","TODO"),
            "tparam",
            "typedef",
            "union",
            "until",
            "var",
            "verbatim",
            "verbinclude",
            "version",
            "warning",
            "weakgroup",
            "xmlonly",
            "xrefitem",
#           "$",
#           "@",
#           "\",
#           "&",
#           "~",
#           "<",
#           ">",
#           "#",
#           "%",
            ]

        for command in replacement_list:
            try:
                old,new = command
            except ValueError:
                old = command
                new = command.capitalize()+":"
            tmp_str = clean(tmp_str, "@"+old, new)
            tmp_str = clean(tmp_str, "\\"+old, new)

                # remove '*/' from the end of the string
        tmp_str = tmp_str.replace("*/", "").lstrip().rstrip()

        return tmp_str
    #clean_str()

    def is_code(self, tmp_str):
        """
        Detects if tmp_str is code or not
        """
        try:
            beg = tmp_str.lstrip()[:2]
            return beg != "//" and beg != "/*"
        except:
            pass
        return False
    #is_code()

#class doxygen_doc_extractor
