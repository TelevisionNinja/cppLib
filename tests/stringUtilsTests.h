#include "../src/unitTest.h"
#include "../src/stringUtils.h"
#include <vector>

template <typename type>
std::string vectorToString(std::vector<type> v) {
    return tvnj::join(v, ", ");
}

void stringUtilsTests() {
    UNIT_TEST_EQ(tvnj::indexOfNaiveSkip("", "a"), -1);
    UNIT_TEST_EQ(tvnj::indexOfNaiveSkip("a", "a"), 0);
    UNIT_TEST_EQ(tvnj::indexOfNaiveSkip("aa", "a"), 0);
    UNIT_TEST_EQ(tvnj::indexOfNaiveSkip("asa", "a"), 0);
    UNIT_TEST_EQ(tvnj::indexOfNaiveSkip("asasa", "basss"), -1);
    UNIT_TEST_EQ(tvnj::indexOfNaiveSkip("aasaa", "basss"), -1);

    UNIT_TEST_EQ(tvnj::indexOfTwoWay("aaaaassssaaasssss", "asssss", 12), -1);
    UNIT_TEST_EQ(tvnj::indexOfTwoWay("aaaaassssaaasssss", "asssss", 11), 11);
    UNIT_TEST_EQ(tvnj::indexOfTwoWay("aaaaassssaaasssss", "asssss"), 11);
    UNIT_TEST_EQ(tvnj::indexOfTwoWay("aaaaassssaaasssss", "assssa"), 4);
    UNIT_TEST_EQ(tvnj::indexOfTwoWay("aaaaasssaaaasssss", "asssaa"), 4);
    UNIT_TEST_EQ(tvnj::indexOfTwoWay("aaaaasssaaaasssss", "asssas"), -1);
    UNIT_TEST_EQ(tvnj::indexOfTwoWay("aaabassbasss", "basss"), 7);
    UNIT_TEST_EQ(tvnj::indexOfTwoWay("aaabassbasss", "b"), 3);
    UNIT_TEST_EQ(tvnj::indexOfTwoWay("aaabassbasss", "ba"), 3);
    UNIT_TEST_EQ(tvnj::indexOfTwoWay("aaabassbasss", "aaabassbasss"), 0);
    UNIT_TEST_EQ(tvnj::indexOfTwoWay("aaaaaaasss", "aaass"), 4);
    UNIT_TEST_EQ(tvnj::indexOfTwoWay("aaaaaaasss", "aass"), 5);

    UNIT_TEST_EQ(tvnj::indexOfNaiveSkip("aaaaassssaaasssss", "asssss", 12), -1);
    UNIT_TEST_EQ(tvnj::indexOfNaiveSkip("aaaaassssaaasssss", "asssss", 11), 11);
    UNIT_TEST_EQ(tvnj::indexOfNaiveSkip("aaaaassssaaasssss", "asssss"), 11);
    UNIT_TEST_EQ(tvnj::indexOfNaiveSkip("aaaaassssaaasssss", "assssa"), 4);
    UNIT_TEST_EQ(tvnj::indexOfNaiveSkip("aaaaasssaaaasssss", "asssaa"), 4);
    UNIT_TEST_EQ(tvnj::indexOfNaiveSkip("aaaaasssaaaasssss", "asssas"), -1);
    UNIT_TEST_EQ(tvnj::indexOfNaiveSkip("aaabassbasss", "basss"), 7);
    UNIT_TEST_EQ(tvnj::indexOfNaiveSkip("aaabassbasss", "b"), 3);
    UNIT_TEST_EQ(tvnj::indexOfNaiveSkip("aaabassbasss", "ba"), 3);
    UNIT_TEST_EQ(tvnj::indexOfNaiveSkip("aaabassbasss", "aaabassbasss"), 0);
    UNIT_TEST_EQ(tvnj::indexOfNaiveSkip("aaaaaaasss", "aaass"), 4);
    UNIT_TEST_EQ(tvnj::indexOfNaiveSkip("aaaaaaasss", "aass"), 5);

    UNIT_TEST_EQ(tvnj::indexOf("aaaaassssaaasssss", "asssss", 12), -1);
    UNIT_TEST_EQ(tvnj::indexOf("aaaaassssaaasssss", "asssss", 11), 11);
    UNIT_TEST_EQ(tvnj::indexOf("aaaaassssaaasssss", "asssss"), 11);
    UNIT_TEST_EQ(tvnj::indexOf("aaaaassssaaasssss", "assssa"), 4);
    UNIT_TEST_EQ(tvnj::indexOf("aaaaasssaaaasssss", "asssaa"), 4);
    UNIT_TEST_EQ(tvnj::indexOf("aaaaasssaaaasssss", "asssas"), -1);
    UNIT_TEST_EQ(tvnj::indexOf("aaabassbasss", "basss"), 7);
    UNIT_TEST_EQ(tvnj::indexOf("aaabassbasss", "b"), 3);
    UNIT_TEST_EQ(tvnj::indexOf("aaabassbasss", "ba"), 3);
    UNIT_TEST_EQ(tvnj::indexOf("aaabassbasss", "aaabassbasss"), 0);
    UNIT_TEST_EQ(tvnj::indexOf("aaaaaaasss", "aaass"), 4);
    UNIT_TEST_EQ(tvnj::indexOf("aaaaaaasss", "aass"), 5);

    std::string aa = "aaaaassssaaasssss",
    bb = "aaabassbasss",

    q = "asssss",
    w = "assssa",
    e = "asssaa",
    r = "asssas",
    t = "basss",
    y = "b",
    u = "ba",
    p = "aaabassbasss";
    UNIT_TEST_EQ(tvnj::replaceAll(aa, q, ""), "aaaaassssaa");
    UNIT_TEST_EQ(tvnj::replaceAll(aa, w, ""), "aaaaaasssss");
    UNIT_TEST_EQ(tvnj::replaceAll(aa, e, ""), "aaaaassssaaasssss");
    UNIT_TEST_EQ(tvnj::replaceAll(aa, r, ""), "aaaaassssaaasssss");
    UNIT_TEST_EQ(tvnj::replaceAll(bb, t, ""), "aaabass");
    UNIT_TEST_EQ(tvnj::replaceAll(bb, y, ""), "aaaassasss");
    UNIT_TEST_EQ(tvnj::replaceAll(bb, u, ""), "aaasssss");
    UNIT_TEST_EQ(tvnj::replaceAll(bb, p, ""), "");

    UNIT_TEST_EQ(tvnj::replaceAll2(aa, q, ""), "aaaaassssaa");
    UNIT_TEST_EQ(tvnj::replaceAll2(aa, w, ""), "aaaaaasssss");
    UNIT_TEST_EQ(tvnj::replaceAll2(aa, e, ""), "aaaaassssaaasssss");
    UNIT_TEST_EQ(tvnj::replaceAll2(aa, r, ""), "aaaaassssaaasssss");
    UNIT_TEST_EQ(tvnj::replaceAll2(bb, t, ""), "aaabass");
    UNIT_TEST_EQ(tvnj::replaceAll2(bb, y, ""), "aaaassasss");
    UNIT_TEST_EQ(tvnj::replaceAll2(bb, u, ""), "aaasssss");
    UNIT_TEST_EQ(tvnj::replaceAll2(bb, p, ""), "");

    UNIT_TEST_EQ(tvnj::indexOfNaiveSkip(aa, q), 11);
    UNIT_TEST_EQ(tvnj::indexOfNaiveSkip(aa, w), 4);
    UNIT_TEST_EQ(tvnj::indexOfNaiveSkip(aa, e), -1);
    UNIT_TEST_EQ(tvnj::indexOfNaiveSkip(aa, r), -1);
    UNIT_TEST_EQ(tvnj::indexOfNaiveSkip(bb, t), 7);
    UNIT_TEST_EQ(tvnj::indexOfNaiveSkip(bb, y), 3);
    UNIT_TEST_EQ(tvnj::indexOfNaiveSkip(bb, u), 3);
    UNIT_TEST_EQ(tvnj::indexOfNaiveSkip(bb, p), 0);

    UNIT_TEST_EQ(tvnj::indexOfNaive(aa, q), 11);
    UNIT_TEST_EQ(tvnj::indexOfNaive(aa, w), 4);
    UNIT_TEST_EQ(tvnj::indexOfNaive(aa, e), -1);
    UNIT_TEST_EQ(tvnj::indexOfNaive(aa, r), -1);
    UNIT_TEST_EQ(tvnj::indexOfNaive(bb, t), 7);
    UNIT_TEST_EQ(tvnj::indexOfNaive(bb, y), 3);
    UNIT_TEST_EQ(tvnj::indexOfNaive(bb, u), 3);
    UNIT_TEST_EQ(tvnj::indexOfNaive(bb, p), 0);

    UNIT_TEST_EQ(tvnj::indexOfNaiveLast(aa, q), 11);
    UNIT_TEST_EQ(tvnj::indexOfNaiveLast(aa, w), 4);
    UNIT_TEST_EQ(tvnj::indexOfNaiveLast(aa, e), -1);
    UNIT_TEST_EQ(tvnj::indexOfNaiveLast(aa, r), -1);
    UNIT_TEST_EQ(tvnj::indexOfNaiveLast(bb, t), 7);
    UNIT_TEST_EQ(tvnj::indexOfNaiveLast(bb, y), 7);
    UNIT_TEST_EQ(tvnj::indexOfNaiveLast(bb, u), 7);
    UNIT_TEST_EQ(tvnj::indexOfNaiveLast(bb, p), 0);

    UNIT_TEST_EQ(tvnj::indexOfNaiveSkipLast(aa, q), 11);
    UNIT_TEST_EQ(tvnj::indexOfNaiveSkipLast(aa, w), 4);
    UNIT_TEST_EQ(tvnj::indexOfNaiveSkipLast(aa, e), -1);
    UNIT_TEST_EQ(tvnj::indexOfNaiveSkipLast(aa, r), -1);
    UNIT_TEST_EQ(tvnj::indexOfNaiveSkipLast(bb, t), 7);
    UNIT_TEST_EQ(tvnj::indexOfNaiveSkipLast(bb, y), 7);
    UNIT_TEST_EQ(tvnj::indexOfNaiveSkipLast(bb, u), 7);
    UNIT_TEST_EQ(tvnj::indexOfNaiveSkipLast(bb, p), 0);

    UNIT_TEST_EQ(vectorToString(tvnj::cmdLnToArgArr("a b d \"asdasd\"", false)), "a, b, d, asdasd");
    UNIT_TEST_EQ(vectorToString(tvnj::cmdLnToArgArr("a b d \"1\"", false)), "a, b, d, 1");
    UNIT_TEST_EQ(vectorToString(tvnj::cmdLnToArgArr("a b d \"\"", false)), "a, b, d, ");
    UNIT_TEST_EQ(vectorToString(tvnj::cmdLnToArgArr("a b d\"\"", false)), "a, b, d, ");
    UNIT_TEST_EQ(vectorToString(tvnj::cmdLnToArgArr("a b d\"", false)), "a, b, d"); // expected: throws an error if true
    UNIT_TEST_EQ(vectorToString(tvnj::cmdLnToArgArr("a b d\\\"", false)), "a, b, d\\"); // expected: throws an error if true

    UNIT_TEST_EQ(vectorToString(tvnj::cmdLnToArgArr("\"22\" a b d", false)), "22, a, b, d");
    UNIT_TEST_EQ(vectorToString(tvnj::cmdLnToArgArr("\"\" a b d", false)), ", a, b, d");
    UNIT_TEST_EQ(vectorToString(tvnj::cmdLnToArgArr("\"\"a b d", false)), ", a, b, d");
    UNIT_TEST_EQ(vectorToString(tvnj::cmdLnToArgArr("\"11\"a b d", false)), "11, a, b, d");

    UNIT_TEST_EQ(vectorToString(tvnj::cmdLnToArgArr("a     b d", false)), "a, b, d");
    UNIT_TEST_EQ(vectorToString(tvnj::cmdLnToArgArr("aa b d   ", false)), "aa, b, d");
    UNIT_TEST_EQ(vectorToString(tvnj::cmdLnToArgArr("  aa   b   ddd   ", false)), "aa, b, ddd");
    UNIT_TEST_EQ(vectorToString(tvnj::cmdLnToArgArr("a     b dddd", false)), "a, b, dddd");

    UNIT_TEST_EQ(vectorToString(tvnj::cmdLnToArgArr("a b d \"asda\"sd\" asd", false)), "a, b, d, asda, sd"); // expected: throws an error if true
    UNIT_TEST_EQ(vectorToString(tvnj::cmdLnToArgArr("a b d \"asda\\\"sd\" asd", false)), "a, b, d, asda\"sd, asd");
    UNIT_TEST_EQ(vectorToString(tvnj::cmdLnToArgArr("a b d \"asda\\\\\"sd\" asd", false)), "a, b, d, asda\\, sd"); // expected: throws an error if true
    UNIT_TEST_EQ(vectorToString(tvnj::cmdLnToArgArr("a b d \"asda\\\\\\\"sd\" asd", false)), "a, b, d, asda\\\"sd, asd");
    UNIT_TEST_EQ(vectorToString(tvnj::cmdLnToArgArr("a b d \"asda\"\"sd\" asd", false)), "a, b, d, asda, sd, asd");

    UNIT_TEST_EQ(tvnj::includesPhrase(" a ", "a"), true);
    UNIT_TEST_EQ(tvnj::includesPhrase("a", "a"), true);
    UNIT_TEST_EQ(tvnj::includesPhrase(" a", "a"), true);
    UNIT_TEST_EQ(tvnj::includesPhrase("a ", "a"), true);
    UNIT_TEST_EQ(tvnj::includesPhrase(" aa ", "a"), false);
    UNIT_TEST_EQ(tvnj::includesPhrase(" aa a ", "a"), true);
    UNIT_TEST_EQ(tvnj::includesPhrase("", "a"), false);
    UNIT_TEST_EQ(tvnj::includesPhrase(" a ", ""), true);

    UNIT_TEST_EQ(tvnj::startsWith("",""), true);
    UNIT_TEST_EQ(tvnj::startsWith("a",""), true);
    UNIT_TEST_EQ(tvnj::startsWith("","a"), false);
    UNIT_TEST_EQ(tvnj::startsWith("a","s"), false);
    UNIT_TEST_EQ(tvnj::startsWith("a","a"), true);
    UNIT_TEST_EQ(tvnj::startsWith("sas","sa"), true);

    UNIT_TEST_EQ(tvnj::endsWith("",""), true);
    UNIT_TEST_EQ(tvnj::endsWith("a",""), true);
    UNIT_TEST_EQ(tvnj::endsWith("","a"), false);
    UNIT_TEST_EQ(tvnj::endsWith("a","s"), false);
    UNIT_TEST_EQ(tvnj::endsWith("a","a"), true);
    UNIT_TEST_EQ(tvnj::endsWith("sas","as"), true);

    UNIT_TEST_EQ(tvnj::repeat("abc", 1), "abc");
    UNIT_TEST_EQ(tvnj::repeat("abc", 0), "");
    UNIT_TEST_EQ(tvnj::repeat("abc", -1), "");
    UNIT_TEST_EQ(tvnj::repeat("abc", 2), "abcabc");
    UNIT_TEST_EQ(tvnj::repeat("abc", 5), "abcabcabcabcabc");

    UNIT_TEST_EQ(tvnj::padLeft("abc", 0,'1'), "abc");
    UNIT_TEST_EQ(tvnj::padLeft("abc", -1,'1'), "abc");
    UNIT_TEST_EQ(tvnj::padLeft("abc", 10,'1'), "1111111abc");
    UNIT_TEST_EQ(tvnj::padLeft("abc", 10), "       abc");

    UNIT_TEST_EQ(tvnj::padRight("abc", 0,'1'), "abc");
    UNIT_TEST_EQ(tvnj::padRight("abc", -1,'1'), "abc");
    UNIT_TEST_EQ(tvnj::padRight("abc", 10,'1'), "abc1111111");
    UNIT_TEST_EQ(tvnj::padRight("abc", 10), "abc       ");

    UNIT_TEST_EQ(tvnj::replaceHTMLEntities(""), "");
    UNIT_TEST_EQ(tvnj::replaceHTMLEntities("a"), "a");
    UNIT_TEST_EQ(tvnj::replaceHTMLEntities("&"), "&");
    UNIT_TEST_EQ(tvnj::replaceHTMLEntities(";"), ";");
    UNIT_TEST_EQ(tvnj::replaceHTMLEntities("&;"), "&;");
    UNIT_TEST_EQ(tvnj::replaceHTMLEntities("&a;"), "&a;");
    UNIT_TEST_EQ(tvnj::replaceHTMLEntities("&amp;"), "&");
    UNIT_TEST_EQ(tvnj::replaceHTMLEntities("&amp;&amp;"), "&&");
    UNIT_TEST_EQ(tvnj::replaceHTMLEntities("&amp&amp;"), "&amp&");
    UNIT_TEST_EQ(tvnj::replaceHTMLEntities("&lt;&gt;&amp;&#39;&apos;&quot;"), "<>&''\"");
    UNIT_TEST_EQ(tvnj::replaceHTMLEntities("&quot;&apos;&#39;&amp;&gt;&lt;"), "\"''&><");
    UNIT_TEST_EQ(tvnj::replaceHTMLEntities("&lt&gt&amp&#39&apos&quot"), "&lt&gt&amp&#39&apos&quot");

    UNIT_TEST_EQ(tvnj::replaceHTMLEntitiesSorted(""), "");
    UNIT_TEST_EQ(tvnj::replaceHTMLEntitiesSorted("a"), "a");
    UNIT_TEST_EQ(tvnj::replaceHTMLEntitiesSorted("&"), "&");
    UNIT_TEST_EQ(tvnj::replaceHTMLEntitiesSorted(";"), ";");
    UNIT_TEST_EQ(tvnj::replaceHTMLEntitiesSorted("&;"), "&;");
    UNIT_TEST_EQ(tvnj::replaceHTMLEntitiesSorted("&a;"), "&a;");
    UNIT_TEST_EQ(tvnj::replaceHTMLEntitiesSorted("&amp;"), "&");
    UNIT_TEST_EQ(tvnj::replaceHTMLEntitiesSorted("&amp;&amp;"), "&&");
    UNIT_TEST_EQ(tvnj::replaceHTMLEntitiesSorted("&amp&amp;"), "&amp&");
    UNIT_TEST_EQ(tvnj::replaceHTMLEntitiesSorted("&lt;&gt;&amp;&#39;&apos;&quot;"), "<>&''\"");
    UNIT_TEST_EQ(tvnj::replaceHTMLEntitiesSorted("&quot;&apos;&#39;&amp;&gt;&lt;"), "\"''&><");
    UNIT_TEST_EQ(tvnj::replaceHTMLEntitiesSorted("&lt&gt&amp&#39&apos&quot"), "&lt&gt&amp&#39&apos&quot");

    std::string testing = "abcdefg";

    UNIT_TEST_EQ(tvnj::slice(testing, 0, 0), "");
    UNIT_TEST_EQ(tvnj::slice(testing, 0, 0, -1), "");
    UNIT_TEST_EQ(tvnj::slice(testing, 0, 0, 1, true), "a");
    UNIT_TEST_EQ(tvnj::slice(testing, 0, 0, -1, true), "a");
    UNIT_TEST_EQ(tvnj::slice(testing, 0, testing.size()), "abcdefg");
    UNIT_TEST_EQ(tvnj::slice(testing, -100000, testing.size(), 1), "abcdefg");
    UNIT_TEST_EQ(tvnj::slice(testing, 0, 100000000), "abcdefg");
    UNIT_TEST_EQ(tvnj::slice(testing, 0, 100000000, 1, true), "abcdefg");
    UNIT_TEST_EQ(tvnj::slice(testing, testing.size(), 0), "");

    UNIT_TEST_EQ(tvnj::slice(testing, -testing.size(), testing.size()), "abcdefg");
    UNIT_TEST_EQ(tvnj::slice(testing, 1, testing.size()), "bcdefg");
    UNIT_TEST_EQ(tvnj::slice(testing, 0, testing.size() - 1), "abcdef");
    UNIT_TEST_EQ(tvnj::slice(testing, 1, testing.size() - 1), "bcdef");

    UNIT_TEST_EQ(tvnj::slice(testing, testing.size(), 0, -1), "gfedcb");
    UNIT_TEST_EQ(tvnj::slice(testing, testing.size(), -10000000, -1), "gfedcba");
    UNIT_TEST_EQ(tvnj::slice(testing, 0, testing.size(), -1), "");
    UNIT_TEST_EQ(tvnj::slice(testing, testing.size()-1, 0, -1), "gfedcb");
    UNIT_TEST_EQ(tvnj::slice(testing, testing.size(), 0, -1, true), "gfedcba");
    UNIT_TEST_EQ(tvnj::slice(testing, testing.size()-1, 0, -1, true), "gfedcba");

    UNIT_TEST_EQ(tvnj::slice(testing, 0, testing.size(), 2), "aceg");

    UNIT_TEST_EQ(tvnj::slice(testing, testing.size(), 0, -2), "gec");
    UNIT_TEST_EQ(tvnj::slice(testing, testing.size(), 0, -2, true), "geca");
    UNIT_TEST_EQ(tvnj::slice(testing, 0, testing.size(), -2), "");

    std::vector<std::string> arrayThing = {"1", "2", "3", "4"};

    UNIT_TEST_EQ(tvnj::join(arrayThing, ", "), "1, 2, 3, 4");
    UNIT_TEST_EQ(tvnj::join(arrayThing, ", ",-1), "");
    UNIT_TEST_EQ(tvnj::join(arrayThing, ", ",0,1000), "1, 2, 3, 4");
    UNIT_TEST_EQ(tvnj::join(arrayThing, ", "-1,-1), "");
    UNIT_TEST_EQ(tvnj::join(arrayThing, ", ",1000), "");
    UNIT_TEST_EQ(tvnj::join(arrayThing, ", ",1000,1000), "");
    UNIT_TEST_EQ(tvnj::join(arrayThing, ", ",0,0), "");
    UNIT_TEST_EQ(tvnj::join(arrayThing, ", ",2,2), "");
    UNIT_TEST_EQ(tvnj::join(arrayThing, ", ",0,1), "1");
    UNIT_TEST_EQ(tvnj::join(arrayThing, ", ",0,2), "1, 2");
    UNIT_TEST_EQ(tvnj::join(arrayThing, ", ",1,2), "2");
    UNIT_TEST_EQ(tvnj::join(arrayThing, ", ",2), "3, 4");
    UNIT_TEST_EQ(tvnj::join(arrayThing, ", ", 2, 1), "");
    UNIT_TEST_EQ(tvnj::join(arrayThing, ", ", 1, 3), "2, 3");
    UNIT_TEST_EQ(tvnj::join(arrayThing, ", ", 1, 4), "2, 3, 4");
    UNIT_TEST_EQ(tvnj::join(arrayThing, ", ", 1, 5), "2, 3, 4");

    UNIT_TEST_EQ(tvnj::replaceNTimesLeft(" a ", "a", "", 1), "  ");
    UNIT_TEST_EQ(tvnj::replaceNTimesLeft("aa", "a", "", 1), "a");
    UNIT_TEST_EQ(tvnj::replaceNTimesLeft("a ", "a", "", 0), "a ");
    UNIT_TEST_EQ(tvnj::replaceNTimesLeft(" aa ", "a", "", 1), " a ");
    UNIT_TEST_EQ(tvnj::replaceNTimesLeft(" aa a ", "a", "", 1), " a a ");
    UNIT_TEST_EQ(tvnj::replaceNTimesLeft("", "a", "", 1), "");
    UNIT_TEST_EQ(tvnj::replaceNTimesLeft(" a ", "", "", 1), " a ");
    UNIT_TEST_EQ(tvnj::replaceNTimesLeft(" a ", "a", "", 2), "  ");
    UNIT_TEST_EQ(tvnj::replaceNTimesLeft("aa", "a", "", 2), "");

    UNIT_TEST_EQ(tvnj::replaceNTimesRight(" a ", "a", "", 1), "  ");
    UNIT_TEST_EQ(tvnj::replaceNTimesRight("aa", "a", "", 1), "a");
    UNIT_TEST_EQ(tvnj::replaceNTimesRight("a ", "a", "", 0), "a ");
    UNIT_TEST_EQ(tvnj::replaceNTimesRight(" aa ", "a", "", 1), " a ");
    UNIT_TEST_EQ(tvnj::replaceNTimesRight(" aa a ", "a", "", 1), " aa  ");
    UNIT_TEST_EQ(tvnj::replaceNTimesRight("", "a", "", 1), "");
    UNIT_TEST_EQ(tvnj::replaceNTimesRight(" a ", "", "", 1), " a ");
    UNIT_TEST_EQ(tvnj::replaceNTimesRight(" a ", "a", "", 2), "  ");
    UNIT_TEST_EQ(tvnj::replaceNTimesRight("aa", "a", "", 2), "");
    UNIT_TEST_EQ(tvnj::replaceNTimesRight("a abb a", "a", "", 2), "a bb ");

    UNIT_TEST_EQ(tvnj::replaceAll(" a ", "a", ""), "  ");
    UNIT_TEST_EQ(tvnj::replaceAll("aa", "a", ""), "");
    UNIT_TEST_EQ(tvnj::replaceAll("a ", "a", ""), " ");
    UNIT_TEST_EQ(tvnj::replaceAll(" aa ", "a", ""), "  ");
    UNIT_TEST_EQ(tvnj::replaceAll(" aa a ", "a", ""), "   ");
    UNIT_TEST_EQ(tvnj::replaceAll("", "a", ""), "");
    UNIT_TEST_EQ(tvnj::replaceAll(" a ", "", ""), " a ");
    UNIT_TEST_EQ(tvnj::replaceAll(" a ", "a", ""), "  ");
    UNIT_TEST_EQ(tvnj::replaceAll("aa", "a", ""), "");
    
    UNIT_TEST_EQ(tvnj::replaceAll2(" a ", "a", ""), "  ");
    UNIT_TEST_EQ(tvnj::replaceAll2("aa", "a", ""), "");
    UNIT_TEST_EQ(tvnj::replaceAll2("a ", "a", ""), " ");
    UNIT_TEST_EQ(tvnj::replaceAll2(" aa ", "a", ""), "  ");
    UNIT_TEST_EQ(tvnj::replaceAll2(" aa a ", "a", ""), "   ");
    UNIT_TEST_EQ(tvnj::replaceAll2("", "a", ""), "");
    UNIT_TEST_EQ(tvnj::replaceAll2(" a ", "", ""), " a ");
    UNIT_TEST_EQ(tvnj::replaceAll2(" a ", "a", ""), "  ");
    UNIT_TEST_EQ(tvnj::replaceAll2("aa", "a", ""), "");

    UNIT_TEST_EQ(tvnj::replaceLast(" a ", "a", ""), "  ");
    UNIT_TEST_EQ(tvnj::replaceLast("aa", "a", ""), "a");
    UNIT_TEST_EQ(tvnj::replaceLast("a ", "a", ""), " ");
    UNIT_TEST_EQ(tvnj::replaceLast(" aa ", "a", ""), " a ");
    UNIT_TEST_EQ(tvnj::replaceLast(" aa a ", "a", ""), " aa  ");
    UNIT_TEST_EQ(tvnj::replaceLast("", "a", ""), "");
    UNIT_TEST_EQ(tvnj::replaceLast(" a ", "", ""), " a ");
    UNIT_TEST_EQ(tvnj::replaceLast(" a ", "a", ""), "  ");
    UNIT_TEST_EQ(tvnj::replaceLast("aa", "a", ""), "a");
    UNIT_TEST_EQ(tvnj::replaceLast("a abb a", "a", ""), "a abb ");

    UNIT_TEST_EQ(tvnj::replaceFirst(" a ", "a", ""), "  ");
    UNIT_TEST_EQ(tvnj::replaceFirst("aa", "a", ""), "a");
    UNIT_TEST_EQ(tvnj::replaceFirst("a ", "a", ""), " ");
    UNIT_TEST_EQ(tvnj::replaceFirst(" aa ", "a", ""), " a ");
    UNIT_TEST_EQ(tvnj::replaceFirst(" aa a ", "a", ""), " a a ");
    UNIT_TEST_EQ(tvnj::replaceFirst("", "a", ""), "");
    UNIT_TEST_EQ(tvnj::replaceFirst(" a ", "", ""), " a ");
    UNIT_TEST_EQ(tvnj::replaceFirst(" a ", "a", ""), "  ");
    UNIT_TEST_EQ(tvnj::replaceFirst("aa", "a", ""), "a");
    UNIT_TEST_EQ(tvnj::replaceFirst("a abb a", "a", ""), " abb a");

    UNIT_TEST_EQ(tvnj::trimLeft("",'a'), "");
    UNIT_TEST_EQ(tvnj::trimLeft("a",'a'), "");
    UNIT_TEST_EQ(tvnj::trimLeft("aa",'a'), "");
    UNIT_TEST_EQ(tvnj::trimLeft("aas",'a'), "s");
    UNIT_TEST_EQ(tvnj::trimLeft("aasa",'a'), "sa");
    UNIT_TEST_EQ(tvnj::trimLeft("saasa",'a'), "saasa");

    UNIT_TEST_EQ(tvnj::trimRight("",'a'), "");
    UNIT_TEST_EQ(tvnj::trimRight("a",'a'), "");
    UNIT_TEST_EQ(tvnj::trimRight("aa",'a'), "");
    UNIT_TEST_EQ(tvnj::trimRight("saa",'a'), "s");
    UNIT_TEST_EQ(tvnj::trimRight("asaa",'a'), "as");
    UNIT_TEST_EQ(tvnj::trimRight("asaas",'a'), "asaas");

    UNIT_TEST_EQ(vectorToString(tvnj::splitWhitespace("")), "");
    UNIT_TEST_EQ(vectorToString(tvnj::splitWhitespace("a")), "a");
    UNIT_TEST_EQ(vectorToString(tvnj::splitWhitespace("a a")), "a, a");
    UNIT_TEST_EQ(vectorToString(tvnj::splitWhitespace("a a a")), "a, a, a");
    UNIT_TEST_EQ(vectorToString(tvnj::splitWhitespace(" a")), ", a");
    UNIT_TEST_EQ(vectorToString(tvnj::splitWhitespace("a ")), "a, ");
    UNIT_TEST_EQ(vectorToString(tvnj::splitWhitespace(" a ")), ", a, ");
    UNIT_TEST_EQ(vectorToString(tvnj::splitWhitespace("   a   a a     a ")), ", a, a, a, a, ");

    UNIT_TEST_EQ(tvnj::alternateStrings("aaaa", "bbbb"), "abababab");
    UNIT_TEST_EQ(tvnj::alternateStrings("aaa", "bbbb"), "abababb");
    UNIT_TEST_EQ(tvnj::alternateStrings("", "bbbb"), "bbbb");
    UNIT_TEST_EQ(tvnj::alternateStrings("aaaa", ""), "aaaa");
    UNIT_TEST_EQ(tvnj::alternateStrings("a", "bbbb"), "abbbb");
    UNIT_TEST_EQ(tvnj::alternateStrings("aaaa", "b"), "abaaa");

    UNIT_TEST_EQ(vectorToString(tvnj::indexOfAllRight("aaaaa", "aa", 0, false)), "0, 2");
    UNIT_TEST_EQ(vectorToString(tvnj::indexOfAllRight("aaaaa", "")), "0");
    UNIT_TEST_EQ(vectorToString(tvnj::indexOfAllRight("aaaaa", "", 10)), "0");
    UNIT_TEST_EQ(vectorToString(tvnj::indexOfAllRight("aaaaa", "", -1)), "0");
    UNIT_TEST_EQ(vectorToString(tvnj::indexOfAllRight("", "aa")), "");
    UNIT_TEST_EQ(vectorToString(tvnj::indexOfAllRight("aaaaa", "aa", 10)), "");
    UNIT_TEST_EQ(vectorToString(tvnj::indexOfAllRight("aaaaa", "aa", -1)), "0, 1, 2, 3");
    UNIT_TEST_EQ(vectorToString(tvnj::indexOfAllRight("aaaaa", "aa", 0, true)), "0, 1, 2, 3");

    UNIT_TEST_NEQ(vectorToString(tvnj::indexOfAllLeft("aaaaa", "aa", -1, false)), "3, 1");
    UNIT_TEST_EQ(vectorToString(tvnj::indexOfAllLeft("aaaaa", "aa", -1, false)), "0, 2");
    UNIT_TEST_EQ(vectorToString(tvnj::indexOfAllLeft("aaaaa", "")), "0");
    UNIT_TEST_EQ(vectorToString(tvnj::indexOfAllLeft("aaaaa", "", 10)), "0");
    UNIT_TEST_EQ(vectorToString(tvnj::indexOfAllLeft("aaaaa", "", -1)), "0");
    UNIT_TEST_EQ(vectorToString(tvnj::indexOfAllLeft("", "aa")), "");
    UNIT_TEST_EQ(vectorToString(tvnj::indexOfAllLeft("aaaaa", "aa", 10)), "0, 1, 2, 3");
    UNIT_TEST_EQ(vectorToString(tvnj::indexOfAllLeft("aaaaa", "aa", -1)), "0, 1, 2, 3");
    UNIT_TEST_EQ(vectorToString(tvnj::indexOfAllLeft("aaaaa", "aa", 0, true)), "");
}
