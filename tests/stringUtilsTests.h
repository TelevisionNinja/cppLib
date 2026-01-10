#ifndef STRINGUTILSTESTS_H
#define STRINGUTILSTESTS_H

#include "../src/unitTest.h"
#include "../src/stringUtils.h"
#include <vector>
#include "../src/data_structures/Trie.h"
#include "../src/data_structures/AhoCorasick.h"
#include "../src/data_structures/AhoCorasickFilter.h"

template <typename type>
std::string vectorToString(std::vector<type> v) {
    return tvnj::join(v, ", ");
}

template <typename type>
std::string vectorPairToString(std::vector<std::pair<type, type>> vec, std::string separator = ", ") {
    size_t n = vec.size();

    if (n == 0) {
        return "";
    }

    n--;

    std::string s = "";

    for (size_t i = 0; i < n; i++) {
        s += "(" + std::to_string(vec[i].first) + " " + std::to_string(vec[i].second) + ")" + separator;
    }

    return s + "(" + std::to_string(vec[n].first) + " " + std::to_string(vec[n].second) + ")";
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
    UNIT_TEST_EQ(tvnj::join(arrayThing, ", ",-1,-1), "");
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

    UNIT_TEST_EQ(tvnj::trim("aaaa", "bbbb"), "aaaa");
    UNIT_TEST_EQ(tvnj::trim("", "bbbb"), "");
    UNIT_TEST_EQ(tvnj::trim("aaaa", ""), "aaaa");
    UNIT_TEST_EQ(tvnj::trim("aaaa", "aa"), "");
    UNIT_TEST_EQ(tvnj::trim("aaaa", "a"), "");
    UNIT_TEST_EQ(tvnj::trim("aaaaa", "aa"), "a");
    UNIT_TEST_EQ(tvnj::trim("aaaabbb", "aa"), "bbb");
    UNIT_TEST_EQ(tvnj::trim("aaaaabbb", "aa"), "abbb");
    UNIT_TEST_EQ(tvnj::trim("aaaab", "aa"), "b");
    UNIT_TEST_EQ(tvnj::trim("aaaab", "a"), "b");
    UNIT_TEST_EQ(tvnj::trim("aaaa", "b"), "aaaa");

    UNIT_TEST_EQ(tvnj::trim("bbbaaaa", "aa"), "bbb");
    UNIT_TEST_EQ(tvnj::trim("bbbaaaaa", "aa"), "bbba");
    UNIT_TEST_EQ(tvnj::trim("baaaa", "aa"), "b");
    UNIT_TEST_EQ(tvnj::trim("baaaa", "a"), "b");
    
    UNIT_TEST_EQ(tvnj::trim("aaaabaaaa", "aa"), "b");
    UNIT_TEST_EQ(tvnj::trim("aaaabaaaa", "a"), "b");
    UNIT_TEST_EQ(tvnj::trim("aaaaabaaaaa", "aa"), "aba");
    UNIT_TEST_EQ(tvnj::trim("aaaaabaaaaa", "a"), "b");
    UNIT_TEST_EQ(tvnj::trim("aaaabaaaaa", "aa"), "ba");
    UNIT_TEST_EQ(tvnj::trim("aaaaabaaaa", "aa"), "ab");

    UNIT_TEST_EQ(tvnj::trimLeft("aaaa", "bbbb"), "aaaa");
    UNIT_TEST_EQ(tvnj::trimLeft("", "bbbb"), "");
    UNIT_TEST_EQ(tvnj::trimLeft("aaaa", ""), "aaaa");
    UNIT_TEST_EQ(tvnj::trimLeft("aaaa", "aa"), "");
    UNIT_TEST_EQ(tvnj::trimLeft("aaaa", "a"), "");
    UNIT_TEST_EQ(tvnj::trimLeft("aaaaa", "aa"), "a");
    UNIT_TEST_EQ(tvnj::trimLeft("aaaabbb", "aa"), "bbb");
    UNIT_TEST_EQ(tvnj::trimLeft("aaaaabbb", "aa"), "abbb");
    UNIT_TEST_EQ(tvnj::trimLeft("aaaab", "aa"), "b");
    UNIT_TEST_EQ(tvnj::trimLeft("aaaab", "a"), "b");
    UNIT_TEST_EQ(tvnj::trimLeft("aaaa", "b"), "aaaa");

    UNIT_TEST_EQ(tvnj::trimRight("aaaa", "bbbb"), "aaaa");
    UNIT_TEST_EQ(tvnj::trimRight("", "bbbb"), "");
    UNIT_TEST_EQ(tvnj::trimRight("aaaa", ""), "aaaa");
    UNIT_TEST_EQ(tvnj::trimRight("aaaa", "aa"), "");
    UNIT_TEST_EQ(tvnj::trimRight("aaaa", "a"), "");
    UNIT_TEST_EQ(tvnj::trimRight("aaaaa", "aa"), "a");
    UNIT_TEST_EQ(tvnj::trimRight("bbbaaaa", "aa"), "bbb");
    UNIT_TEST_EQ(tvnj::trimRight("bbbaaaaa", "aa"), "bbba");
    UNIT_TEST_EQ(tvnj::trimRight("baaaa", "aa"), "b");
    UNIT_TEST_EQ(tvnj::trimRight("baaaa", "a"), "b");
    UNIT_TEST_EQ(tvnj::trimRight("aaaa", "b"), "aaaa");

    std::vector<std::string> right = {"aae", "aa", "b", "c"},
        left = {"aae", "aa", "b", "c"},
        other = {"aae", "eaa", "aa", "b", "c"},
        emptyVec = {};

    UNIT_TEST_EQ(tvnj::trimLeft("aaaa", left), "");
    UNIT_TEST_EQ(tvnj::trimLeft("", left), "");
    UNIT_TEST_EQ(tvnj::trimLeft("aabc", left), "");
    UNIT_TEST_EQ(tvnj::trimLeft("bcaa", left), "");
    UNIT_TEST_EQ(tvnj::trimLeft("aasb", left), "sb");
    UNIT_TEST_EQ(tvnj::trimLeft("saab", left), "saab");
    UNIT_TEST_EQ(tvnj::trimLeft("aabs", left), "s");
    UNIT_TEST_EQ(tvnj::trimLeft("aaeaa", left), "");
    UNIT_TEST_EQ(tvnj::trimLeft("aaaa", emptyVec), "aaaa");

    UNIT_TEST_EQ(tvnj::trimRight("aaaa", right), "");
    UNIT_TEST_EQ(tvnj::trimRight("", right), "");
    UNIT_TEST_EQ(tvnj::trimRight("aabc", right), "");
    UNIT_TEST_EQ(tvnj::trimRight("bcaa", right), "");
    UNIT_TEST_EQ(tvnj::trimRight("aasb", right), "aas");
    UNIT_TEST_EQ(tvnj::trimRight("saab", right), "s");
    UNIT_TEST_EQ(tvnj::trimRight("aabs", right), "aabs");
    UNIT_TEST_EQ(tvnj::trimRight("aaeaa", right), "");
    UNIT_TEST_EQ(tvnj::trimRight("aaaa", emptyVec), "aaaa");

    UNIT_TEST_EQ(tvnj::trim("aaaa", left), "");
    UNIT_TEST_EQ(tvnj::trim("", left), "");
    UNIT_TEST_EQ(tvnj::trim("aabc", left), "");
    UNIT_TEST_EQ(tvnj::trim("bcaa", left), "");
    UNIT_TEST_EQ(tvnj::trim("aasb", left), "s");
    UNIT_TEST_EQ(tvnj::trim("saab", left), "s");
    UNIT_TEST_EQ(tvnj::trim("aabs", left), "s");
    UNIT_TEST_EQ(tvnj::trim("aaeaa", left), "");
    UNIT_TEST_EQ(tvnj::trim("aaseaa", left), "se");
    UNIT_TEST_EQ(tvnj::trim("aaseaa", other), "s");
    UNIT_TEST_EQ(tvnj::trim("aaesaa", left), "s");
    UNIT_TEST_EQ(tvnj::trim("aasesaa", left), "ses");
    UNIT_TEST_EQ(tvnj::trim("aaaa", emptyVec), "aaaa");

    UNIT_TEST_EQ(vectorToString(tvnj::split("", "")), "");
    UNIT_TEST_EQ(vectorToString(tvnj::split("x", "x")), ", ");

    UNIT_TEST_EQ(vectorToString(tvnj::split("axa", "x")), "a, a");
    UNIT_TEST_EQ(vectorToString(tvnj::split("xa", "x")), ", a");
    UNIT_TEST_EQ(vectorToString(tvnj::split("ax", "x")), "a, ");
    UNIT_TEST_EQ(vectorToString(tvnj::split("axaxa", "x")), "a, a, a");
    UNIT_TEST_EQ(vectorToString(tvnj::split("xaxaxa", "x")), ", a, a, a");
    UNIT_TEST_EQ(vectorToString(tvnj::split("axaxax", "x")), "a, a, a, ");
    UNIT_TEST_EQ(vectorToString(tvnj::split("xaxaxax", "x")), ", a, a, a, ");
    UNIT_TEST_EQ(vectorToString(tvnj::split("axxa", "x")), "a, , a");

    UNIT_TEST_EQ(vectorToString(tvnj::split("axxa", "xx")), "a, a");
    UNIT_TEST_EQ(vectorToString(tvnj::split("axxaxxa", "xx")), "a, a, a");
    UNIT_TEST_EQ(vectorToString(tvnj::split("axxaxx", "xx")), "a, a, ");
    UNIT_TEST_EQ(vectorToString(tvnj::split("xxaxxa", "xx")), ", a, a");
    UNIT_TEST_EQ(vectorToString(tvnj::split("xxaxxaxx", "xx")), ", a, a, ");

    UNIT_TEST_EQ(vectorToString(tvnj::split("abcxxabc", "xx")), "abc, abc");
    UNIT_TEST_EQ(vectorToString(tvnj::split("abcxxabcxxabc", "xx")), "abc, abc, abc");
    UNIT_TEST_EQ(vectorToString(tvnj::split("abcxxabcxx", "xx")), "abc, abc, ");
    UNIT_TEST_EQ(vectorToString(tvnj::split("xxabcxxabc", "xx")), ", abc, abc");
    UNIT_TEST_EQ(vectorToString(tvnj::split("xxabcxxabcxx", "xx")), ", abc, abc, ");

    UNIT_TEST_EQ(vectorToString(tvnj::splitNTimesLeft("", "", 0)), "");
    UNIT_TEST_EQ(vectorToString(tvnj::splitNTimesLeft("", "", -1)), "");
    UNIT_TEST_EQ(vectorToString(tvnj::splitNTimesLeft("", "", 1)), "");
    UNIT_TEST_EQ(vectorToString(tvnj::splitNTimesLeft("x", "x", 1)), ", ");

    UNIT_TEST_EQ(vectorToString(tvnj::splitNTimesLeft("axa", "x", 1)), "a, a");
    UNIT_TEST_EQ(vectorToString(tvnj::splitNTimesLeft("xa", "x", 1)), ", a");
    UNIT_TEST_EQ(vectorToString(tvnj::splitNTimesLeft("ax", "x", 1)), "a, ");
    UNIT_TEST_EQ(vectorToString(tvnj::splitNTimesLeft("axaxa", "x", 1)), "a, axa");
    UNIT_TEST_EQ(vectorToString(tvnj::splitNTimesLeft("xaxaxa", "x", 1)), ", axaxa");
    UNIT_TEST_EQ(vectorToString(tvnj::splitNTimesLeft("axaxax", "x", 1)), "a, axax");
    UNIT_TEST_EQ(vectorToString(tvnj::splitNTimesLeft("xaxaxax", "x", 1)), ", axaxax");
    UNIT_TEST_EQ(vectorToString(tvnj::splitNTimesLeft("axxa", "x", 1)), "a, xa");

    UNIT_TEST_EQ(vectorToString(tvnj::splitNTimesLeft("axyza", "xyz", 1)), "a, a");
    UNIT_TEST_EQ(vectorToString(tvnj::splitNTimesLeft("axyzaxyza", "xyz", 1)), "a, axyza");
    UNIT_TEST_EQ(vectorToString(tvnj::splitNTimesLeft("axyzaxyz", "xyz", 1)), "a, axyz");
    UNIT_TEST_EQ(vectorToString(tvnj::splitNTimesLeft("xyzaxyza", "xyz", 1)), ", axyza");
    UNIT_TEST_EQ(vectorToString(tvnj::splitNTimesLeft("xyzaxyzaxyz", "xyz", 1)), ", axyzaxyz");

    UNIT_TEST_EQ(vectorToString(tvnj::splitNTimesLeft("abcxyzabc", "xyz", 1)), "abc, abc");
    UNIT_TEST_EQ(vectorToString(tvnj::splitNTimesLeft("abcxyzabcxyzabc", "xyz", 1)), "abc, abcxyzabc");
    UNIT_TEST_EQ(vectorToString(tvnj::splitNTimesLeft("abcxyzabcxyz", "xyz", 1)), "abc, abcxyz");
    UNIT_TEST_EQ(vectorToString(tvnj::splitNTimesLeft("xyzabcxyzabc", "xyz", 1)), ", abcxyzabc");
    UNIT_TEST_EQ(vectorToString(tvnj::splitNTimesLeft("xyzabcxyzabcxyz", "xyz", 1)), ", abcxyzabcxyz");
    UNIT_TEST_EQ(vectorToString(tvnj::splitNTimesLeft("xyzabcxyzabcxyz", "xyz", 1, 3)), "xyzabc, abcxyz");
    UNIT_TEST_EQ(vectorToString(tvnj::splitNTimesLeft("xyzabcxyzabcxyz", "xyz", 10)), ", abc, abc, ");
    UNIT_TEST_EQ(vectorToString(tvnj::splitNTimesLeft("xabd1234xabexabe", "xabd", 2)), ", 1234xabexabe");
    UNIT_TEST_EQ(vectorToString(tvnj::splitNTimesLeft("xabxd1234xabxexabxe", "xabxd", 2)), ", 1234xabxexabxe");

    UNIT_TEST_EQ(vectorToString(tvnj::splitNTimesRight("", "", 0)), "");
    UNIT_TEST_EQ(vectorToString(tvnj::splitNTimesRight("", "", -1)), "");
    UNIT_TEST_EQ(vectorToString(tvnj::splitNTimesRight("", "", 1)), "");
    UNIT_TEST_EQ(vectorToString(tvnj::splitNTimesRight("x", "x", 1)), ", ");

    UNIT_TEST_EQ(vectorToString(tvnj::splitNTimesRight("axa", "x", 1)), "a, a");
    UNIT_TEST_EQ(vectorToString(tvnj::splitNTimesRight("xa", "x", 1)), ", a");
    UNIT_TEST_EQ(vectorToString(tvnj::splitNTimesRight("ax", "x", 1)), "a, ");
    UNIT_TEST_EQ(vectorToString(tvnj::splitNTimesRight("axaxa", "x", 1)), "axa, a");
    UNIT_TEST_EQ(vectorToString(tvnj::splitNTimesRight("xaxaxa", "x", 1)), "xaxa, a");
    UNIT_TEST_EQ(vectorToString(tvnj::splitNTimesRight("axaxax", "x", 1)), "axaxa, ");
    UNIT_TEST_EQ(vectorToString(tvnj::splitNTimesRight("xaxaxax", "x", 1)), "xaxaxa, ");
    UNIT_TEST_EQ(vectorToString(tvnj::splitNTimesRight("axxa", "x", 1)), "ax, a");

    UNIT_TEST_EQ(vectorToString(tvnj::splitNTimesRight("axyza", "xyz", 1)), "a, a");
    UNIT_TEST_EQ(vectorToString(tvnj::splitNTimesRight("axyzaxyza", "xyz", 1)), "axyza, a");
    UNIT_TEST_EQ(vectorToString(tvnj::splitNTimesRight("axyzaxyz", "xyz", 1)), "axyza, ");
    UNIT_TEST_EQ(vectorToString(tvnj::splitNTimesRight("xyzaxyza", "xyz", 1)), "xyza, a");
    UNIT_TEST_EQ(vectorToString(tvnj::splitNTimesRight("xyzaxyzaxyz", "xyz", 1)), "xyzaxyza, ");

    UNIT_TEST_EQ(vectorToString(tvnj::splitNTimesRight("abcxyzabc", "xyz", 1)), "abc, abc");
    UNIT_TEST_EQ(vectorToString(tvnj::splitNTimesRight("abcxyzabcxyzabc", "xyz", 1)), "abcxyzabc, abc");
    UNIT_TEST_EQ(vectorToString(tvnj::splitNTimesRight("abcxyzabcxyz", "xyz", 1)), "abcxyzabc, ");
    UNIT_TEST_EQ(vectorToString(tvnj::splitNTimesRight("xyzabcxyzabc", "xyz", 1)), "xyzabc, abc");
    UNIT_TEST_EQ(vectorToString(tvnj::splitNTimesRight("xyzabcxyzabcxyz", "xyz", 1)), "xyzabcxyzabc, ");
    UNIT_TEST_EQ(vectorToString(tvnj::splitNTimesRight("xyzabcxyzabcxyz", "xyz", 1, 3)), ", abcxyzabcxyz");
    UNIT_TEST_EQ(vectorToString(tvnj::splitNTimesRight("xyzabcxyzabcxyz", "xyz", 10)), ", abc, abc, ");
    UNIT_TEST_EQ(vectorToString(tvnj::splitNTimesRight("dabx1234eabxeabx", "dabx", 2)), ", 1234eabxeabx");
    UNIT_TEST_EQ(vectorToString(tvnj::splitNTimesRight("dxabx1234exabxexabx", "dxabx", 2)), ", 1234exabxexabx");

    UNIT_TEST_EQ(vectorToString(tvnj::splitNTimesLeft("", 'x', 1)), "");
    UNIT_TEST_EQ(vectorToString(tvnj::splitNTimesLeft("x", 'x', -1)), "x");
    UNIT_TEST_EQ(vectorToString(tvnj::splitNTimesLeft("x", 'x', 0)), "x");
    UNIT_TEST_EQ(vectorToString(tvnj::splitNTimesLeft("x", 'x', 1)), ", ");
    UNIT_TEST_EQ(vectorToString(tvnj::splitNTimesLeft("x", 'x', 10)), ", ");

    UNIT_TEST_EQ(vectorToString(tvnj::splitNTimesLeft("axa", 'x', 1)), "a, a");
    UNIT_TEST_EQ(vectorToString(tvnj::splitNTimesLeft("xa", 'x', 1)), ", a");
    UNIT_TEST_EQ(vectorToString(tvnj::splitNTimesLeft("ax", 'x', 1)), "a, ");
    UNIT_TEST_EQ(vectorToString(tvnj::splitNTimesLeft("axaxa", 'x', 1)), "a, axa");
    UNIT_TEST_EQ(vectorToString(tvnj::splitNTimesLeft("xaxaxa", 'x', 1)), ", axaxa");
    UNIT_TEST_EQ(vectorToString(tvnj::splitNTimesLeft("axaxax", 'x', 1)), "a, axax");
    UNIT_TEST_EQ(vectorToString(tvnj::splitNTimesLeft("xaxaxax", 'x', 1)), ", axaxax");
    UNIT_TEST_EQ(vectorToString(tvnj::splitNTimesLeft("axxa", 'x', 1)), "a, xa");

    UNIT_TEST_NEQ(vectorToString(tvnj::splitNTimesLeft("axxa", 'x', 1, 1)), ", xa");
    UNIT_TEST_EQ(vectorToString(tvnj::splitNTimesLeft("axxa", 'x', 1, 1)), "a, xa");

    UNIT_TEST_NEQ(vectorToString(tvnj::splitNTimesLeft("axxa", 'x', 2, 1)), ", , a");
    UNIT_TEST_EQ(vectorToString(tvnj::splitNTimesLeft("axxa", 'x', 2, 1)), "a, , a");

    UNIT_TEST_EQ(vectorToString(tvnj::splitNTimesLeft("axaxa", 'x', 2)), "a, a, a");
    UNIT_TEST_EQ(vectorToString(tvnj::splitNTimesLeft("xaxaxa", 'x', 2)), ", a, axa");
    UNIT_TEST_EQ(vectorToString(tvnj::splitNTimesLeft("axaxax", 'x', 2)), "a, a, ax");
    UNIT_TEST_EQ(vectorToString(tvnj::splitNTimesLeft("xaxaxax", 'x', 2)), ", a, axax");
    UNIT_TEST_EQ(vectorToString(tvnj::splitNTimesLeft("axxa", 'x', 2)), "a, , a");

    UNIT_TEST_EQ(vectorToString(tvnj::splitNTimesRight("", 'x', 1)), "");
    UNIT_TEST_EQ(vectorToString(tvnj::splitNTimesRight("x", 'x', -1)), "x");
    UNIT_TEST_EQ(vectorToString(tvnj::splitNTimesRight("x", 'x', 0)), "x");
    UNIT_TEST_EQ(vectorToString(tvnj::splitNTimesRight("x", 'x', 1)), ", ");
    UNIT_TEST_EQ(vectorToString(tvnj::splitNTimesRight("x", 'x', 10)), ", ");

    UNIT_TEST_EQ(vectorToString(tvnj::splitNTimesRight("axa", 'x', 1)), "a, a");
    UNIT_TEST_EQ(vectorToString(tvnj::splitNTimesRight("xa", 'x', 1)), ", a");
    UNIT_TEST_EQ(vectorToString(tvnj::splitNTimesRight("ax", 'x', 1)), "a, ");
    UNIT_TEST_EQ(vectorToString(tvnj::splitNTimesRight("axaxa", 'x', 1)), "axa, a");
    UNIT_TEST_EQ(vectorToString(tvnj::splitNTimesRight("xaxaxa", 'x', 1)), "xaxa, a");
    UNIT_TEST_EQ(vectorToString(tvnj::splitNTimesRight("axaxax", 'x', 1)), "axaxa, ");
    UNIT_TEST_EQ(vectorToString(tvnj::splitNTimesRight("xaxaxax", 'x', 1)), "xaxaxa, ");
    UNIT_TEST_EQ(vectorToString(tvnj::splitNTimesRight("axxa", 'x', 1)), "ax, a");

    UNIT_TEST_NEQ(vectorToString(tvnj::splitNTimesRight("axxa", 'x', 1, 2)), "ax, ");
    UNIT_TEST_EQ(vectorToString(tvnj::splitNTimesRight("axxa", 'x', 1, 2)), "ax, a");

    UNIT_TEST_NEQ(vectorToString(tvnj::splitNTimesRight("axxa", 'x', 2, 2)), "a, , ");
    UNIT_TEST_EQ(vectorToString(tvnj::splitNTimesRight("axxa", 'x', 2, 2)), "a, , a");

    UNIT_TEST_EQ(vectorToString(tvnj::splitNTimesRight("axaxa", 'x', 2)), "a, a, a");
    UNIT_TEST_EQ(vectorToString(tvnj::splitNTimesRight("xaxaxa", 'x', 2)), "xa, a, a");
    UNIT_TEST_EQ(vectorToString(tvnj::splitNTimesRight("axaxax", 'x', 2)), "axa, a, ");
    UNIT_TEST_EQ(vectorToString(tvnj::splitNTimesRight("xaxaxax", 'x', 2)), "xaxa, a, ");
    UNIT_TEST_EQ(vectorToString(tvnj::splitNTimesRight("axxa", 'x', 2)), "a, , a");

    std::vector<int> join1 = {};
    UNIT_TEST_EQ(tvnj::join(join1), "");
    join1 = {1};
    UNIT_TEST_EQ(tvnj::join(join1), "1");
    join1 = {1,2};
    UNIT_TEST_EQ(tvnj::join(join1), "1 2");

    std::vector<char> join2 = {};
    UNIT_TEST_EQ(tvnj::join(join2), "");
    join2 = {'a'};
    UNIT_TEST_EQ(tvnj::join(join2), "a");
    join2 = {'a','b'};
    UNIT_TEST_EQ(tvnj::join(join2), "a b");

    std::vector<std::string> join3 = {};
    UNIT_TEST_EQ(tvnj::join(join3), "");
    join3 = {"a"};
    UNIT_TEST_EQ(tvnj::join(join3), "a");
    join3 = {"a","b"};
    UNIT_TEST_EQ(tvnj::join(join3), "a b");

    std::vector<std::string> join4 = {};
    UNIT_TEST_EQ(tvnj::join(join4), "");
    UNIT_TEST_NEQ(tvnj::join(join4), " ");
    join4 = {"aa"};
    UNIT_TEST_EQ(tvnj::join(join4), "aa");
    join4 = {"a","bb"};
    UNIT_TEST_EQ(tvnj::join(join4), "a bb");
    UNIT_TEST_NEQ(tvnj::join(join4), "abb");
    join4 = {"a","bb",""};
    UNIT_TEST_EQ(tvnj::join(join4), "a bb ");
    UNIT_TEST_NEQ(tvnj::join(join4), "a bb");
    join4 = {"","a","bb"};
    UNIT_TEST_EQ(tvnj::join(join4), " a bb");
    UNIT_TEST_NEQ(tvnj::join(join4), "a bb");
    join4 = {"a","","bb"};
    UNIT_TEST_EQ(tvnj::join(join4), "a  bb");
    UNIT_TEST_NEQ(tvnj::join(join4), "a bb");

    UNIT_TEST_EQ(tvnj::sanitizeMarkupLanguage(
        "<script> </script>"
        "<script></script>"
        "<scripta>"
        " asdasd"
        "</scripta>"
        "\n"
        "<scriptb ></scriptb>"
        "<scriptb a=\"\"></scriptb>"
        "<scriptc a=\"\"b=\"\"></scriptc>"
        "<scriptd a=\"\" b=\"\"></scriptd>"
        "<scriptg a=\">\" b=\"\"></scriptg>"
        "<scripth a=\">\" b=\""
        "\"></scripth>"
        "<scripti a=\"\" b=\""
        "\"></scripti>"
        "\n"
        "<scripte>"
        "    // </scripte>"
        "</scripte>"
        "\n"
        "<scriptf>"
        "    /*"
        "    </scriptf>"
        "    */"
        "</scriptf>"
        "\n"
        "<br/>"
        "<br />"
        "<img src=\"image.jpg\" alt=\"An image>\" />"
        "<img src=\"image.jpg\" alt=\"An image/>\" />"
        "<img src=\"image.jpg\"alt=\"An image/>\" />"
        "\n"
        "<!-- comment -->", {
            "script",
            "scripta",
            "scriptb",
            "scriptc",
            "scriptd",
            "scripte",
            "scriptf",
            "scriptg",
            "scripth",
            "scripti",
            "br",
            "img"
        }, {}), "\n\n\n\n\n<!-- comment -->");

    UNIT_TEST_EQ(tvnj::sanitizeMarkupLanguage(
        "<script> </script>"
        "<script></script>"
        "<scripta>"
        " asdasd"
        "</scripta>"
        "\n"
        "<scriptb ></scriptb>"
        "<scriptb a=\"\"></scriptb>"
        "<scriptc a=\"\"b=\"\"></scriptc>"
        "<scriptd a=\"\" b=\"\"></scriptd>"
        "<scriptg a=\">\" b=\"\"></scriptg>"
        "<scripth a=\">\" b=\""
        "\"></scripth>"
        "<scripti a=\"\" b=\""
        "\"></scripti>"
        "\n"
        "<scripte>"
        "    // </scripte>"
        "</scripte>"
        "\n"
        "<scriptf>"
        "    /*"
        "    </scriptf>"
        "    */"
        "</scriptf>"
        "\n"
        "<br/>"
        "<br />"
        "<img src=\"image.jpg\" alt=\"An image>\" />"
        "<img src=\"image.jpg\" alt=\"An image/>\" />"
        "<img src=\"image.jpg\"alt=\"An image/>\" />"
        "\n"
        "<!-- comment -->", {
            "script",
            "scriptA",
            "scriptb",
            "scriptc",
            "scriptd",
            "scripte",
            "scriptf",
            "scriptg",
            "scripth",
            "scripti",
            "br",
            "img"
        }, {}), "\n\n\n\n\n<!-- comment -->");

    UNIT_TEST_NEQ(tvnj::isAllowedMarkupLanguage(
        "<script> </script>"
        "<script></script>"
        "<scripta>"
        " asdasd"
        "</scripta>"
        "\n"
        "<scriptb ></scriptb>"
        "<scriptb a=\"\"></scriptb>"
        "<scriptc a=\"\"b=\"\"></scriptc>"
        "<scriptd a=\"\" b=\"\"></scriptd>"
        "<scriptg a=\">\" b=\"\"></scriptg>"
        "<scripth a=\">\" b=\""
        "\"></scripth>"
        "<scripti a=\"\" b=\""
        "\"></scripti>"
        "\n"
        "<scripte>"
        "    // </scripte>"
        "</scripte>"
        "\n"
        "<scriptf>"
        "    /*"
        "    </scriptf>"
        "    */"
        "</scriptf>"
        "\n"
        "<br/>"
        "<br />"
        "<img src=\"image.jpg\" alt=\"An image>\" />"
        "<img src=\"image.jpg\" alt=\"An image/>\" />"
        "<img src=\"image.jpg\"alt=\"An image/>\" />"
        "\n"
        "<!-- comment -->", {
            "script",
            "scriptA",
            "scriptb",
            "scriptc",
            "scriptd",
            "scripte",
            "scriptf",
            "scriptg",
            "scripth",
            "scripti",
            "br",
            "img"
        }, {}), true);

    UNIT_TEST_EQ(tvnj::isAllowedMarkupLanguage(
        "<script> </script>"
        "<script></script>"
        "<scripta>"
        " asdasd"
        "</scripta>"
        "\n"
        "<scriptb ></scriptb>"
        "<scriptb a=\"\"></scriptb>"
        "<scriptc a=\"\"b=\"\"></scriptc>"
        "<scriptd a=\"\" b=\"\"></scriptd>"
        "<scriptg a=\">\" b=\"\"></scriptg>"
        "<scripth a=\">\" b=\""
        "\"></scripth>"
        "<scripti a=\"\" b=\""
        "\"></scripti>"
        "\n"
        "<scripte>"
        "    // </scripte>"
        "</scripte>"
        "\n"
        "<scriptf>"
        "    /*"
        "    </scriptf>"
        "    */"
        "</scriptf>"
        "\n"
        "<br/>"
        "<br />"
        "<img src=\"image.jpg\" alt=\"An image>\" />"
        "<img src=\"image.jpg\" alt=\"An image/>\" />"
        "<img src=\"image.jpg\"alt=\"An image/>\" />"
        "\n"
        "<!-- comment -->", {
            "script",
            "scriptA",
            "scriptb",
            "scriptc",
            "scriptd",
            "scripte",
            "scriptf",
            "scriptg",
            "scripth",
            "scripti",
            "br",
            "img"
        }, {}), false);

    UNIT_TEST_EQ(tvnj::isAllowedMarkupLanguage(
        "<script> </script>"
        "<script></script>"
        "<scripta>"
        " asdasd"
        "</scripta>"
        "\n"
        "<scriptb ></scriptb>"
        "<scriptb a=\"\"></scriptb>"
        "<scriptc a=\"\"b=\"\"></scriptc>"
        "<scriptd a=\"\" b=\"\"></scriptd>"
        "<scriptg a=\">\" b=\"\"></scriptg>"
        "<scripth a=\">\" b=\""
        "\"></scripth>"
        "<scripti a=\"\" b=\""
        "\"></scripti>"
        "\n"
        "<scripte>"
        "    // </scripte>"
        "</scripte>"
        "\n"
        "<scriptf>"
        "    /*"
        "    </scriptf>"
        "    */"
        "</scriptf>"
        "\n"
        "<br/>"
        "<br />"
        "<img src=\"image.jpg\" alt=\"An image>\" />"
        "<img src=\"image.jpg\" alt=\"An image/>\" />"
        "<img src=\"image.jpg\"alt=\"An image/>\" />"
        "\n"
        "<!-- comment -->", {
            "script"
        }, {}), false);

    UNIT_TEST_EQ(tvnj::isAllowedMarkupLanguage(
        "<script> </script>"
        "<!-- comment -->", {
            "scriptA",
            "scriptb",
            "scriptc",
            "scriptd",
            "scripte",
            "scriptf",
            "scriptg",
            "scripth",
            "scripti",
            "br",
            "img"
        }, {}), true);

    UNIT_TEST_EQ(tvnj::sanitizeMarkupLanguage(
        "<h1> </h1>", {
            "script",
            "scripta",
            "scriptb",
            "scriptc",
            "scriptd",
            "scripte",
            "scriptf",
            "scriptg",
            "scripth",
            "scripti",
            "br",
            "img"
        }, {}), "<h1> </h1>");

    UNIT_TEST_EQ(tvnj::sanitizeMarkupLanguage(
        "<h1> </h1>", {
            "h1",
            "script",
            "scripta",
            "scriptb",
            "scriptc",
            "scriptd",
            "scripte",
            "scriptf",
            "scriptg",
            "scripth",
            "scripti",
            "br",
            "img"
        }, {}), "");

    UNIT_TEST_EQ(tvnj::sanitizeMarkupLanguage(
        "<h1> </h1>", {
            "script",
            "scripta",
            "scriptb",
            "scriptc",
            "scriptd",
            "scripte",
            "scriptf",
            "scriptg",
            "scripth",
            "scripti",
            "br",
            "img"
        }, { "h1" }), "<h1> </h1>");

    UNIT_TEST_EQ(tvnj::sanitizeMarkupLanguage(
        "<h1> </h1>", {
            "h1",
            "script",
            "scripta",
            "scriptb",
            "scriptc",
            "scriptd",
            "scripte",
            "scriptf",
            "scriptg",
            "scripth",
            "scripti",
            "br",
            "img"
        }, { "h1" }), "");

    UNIT_TEST_EQ(tvnj::isAllowedMarkupLanguage(
        "<h1> </h1>", {
            "scriptA",
            "scriptb",
            "scriptc",
            "scriptd",
            "scripte",
            "scriptf",
            "scriptg",
            "scripth",
            "scripti",
            "br",
            "img"
        }, {}), true);

    UNIT_TEST_EQ(tvnj::isAllowedMarkupLanguage(
        "<h1> </h1>", {
            "h1",
            "scriptb",
            "scriptc",
            "scriptd",
            "scripte",
            "scriptf",
            "scriptg",
            "scripth",
            "scripti",
            "br",
            "img"
        }, {}), false);

    UNIT_TEST_EQ(tvnj::isAllowedMarkupLanguage(
        "<h1> </h1>", {
            "scriptA",
            "scriptb",
            "scriptc",
            "scriptd",
            "scripte",
            "scriptf",
            "scriptg",
            "scripth",
            "scripti",
            "br",
            "img"
        }, { "h1" }), true);

    UNIT_TEST_EQ(tvnj::isAllowedMarkupLanguage(
        "<h1> </h1>", {
            "h1",
            "scriptb",
            "scriptc",
            "scriptd",
            "scripte",
            "scriptf",
            "scriptg",
            "scripth",
            "scripti",
            "br",
            "img"
        }, { "h1" }), false);

    UNIT_TEST_EQ(tvnj::sanitizeSVG("<math><mi//xlink:href=\"data:x,<script>alert(4)</script>\">"), "<math><mi//xlink:href=\"data:x,\">");

    UNIT_TEST_EQ(tvnj::sanitizeMarkupLanguage(
        "<script> </script>"
        "<script></script>"
        "<scripta>"
        " asdasd"
        "</scripta>"
        "\n"
        "<scriptb ></scriptb>"
        "<scriptb a=\"\"></scriptb>"
        "<scriptc a=\"\"b=\"\"></scriptc>"
        "<scriptd a=\"\" b=\"\"></scriptd>"
        "<scriptg a=\">\" b=\"\"></scriptg>"
        "<scripth a=\">\" b=\""
        "\"></scripth>"
        "<scripti a=\"\" b=\""
        "\"></scripti>"
        "\n"
        "<scripte>"
        "    // </scripte>"
        "</scripte>"
        "\n"
        "<scriptf>"
        "    /*"
        "    </scriptf>"
        "    */"
        "</scriptf>"
        "\n"
        "<br/>"
        "<br />"
        "<img src=\"image.jpg\" alt=\"An image>\" />"
        "<img src=\"image.jpg\" alt=\"An image/>\" />"
        "<img src=\"image.jpg\"alt=\"An image/>\" />"
        "\n"
        "<!-- comment -->", {
            "animate",
            "color-profile",
            "cursor",
            "discard",
            "font-face",
            "font-face-format",
            "font-face-name",
            "font-face-src",
            "font-face-uri",
            "foreignobject",
            "hatch",
            "hatchpath",
            "mesh",
            "meshgradient",
            "meshpatch",
            "meshrow",
            "missing-glyph",
            "script",
            "set",
            "solidcolor",
            "unknown",
            "use"
        }, {}),
        "<scripta>"
        " asdasd"
        "</scripta>"
        "\n"
        "<scriptb ></scriptb>"
        "<scriptb a=\"\"></scriptb>"
        "<scriptc a=\"\"b=\"\"></scriptc>"
        "<scriptd a=\"\" b=\"\"></scriptd>"
        "<scriptg a=\">\" b=\"\"></scriptg>"
        "<scripth a=\">\" b=\""
        "\"></scripth>"
        "<scripti a=\"\" b=\""
        "\"></scripti>"
        "\n"
        "<scripte>"
        "    // </scripte>"
        "</scripte>"
        "\n"
        "<scriptf>"
        "    /*"
        "    </scriptf>"
        "    */"
        "</scriptf>"
        "\n"
        "<br/>"
        "<br />"
        "<img src=\"image.jpg\" alt=\"An image>\" />"
        "<img src=\"image.jpg\" alt=\"An image/>\" />"
        "<img src=\"image.jpg\"alt=\"An image/>\" />"
        "\n"
        "<!-- comment -->");

    UNIT_TEST_EQ(tvnj::sanitizeMarkupLanguage(
        "<script> </script>"
        "<script></script>"
        "<scripta>"
        " asdasd"
        "</scripta>"
        "\n"
        "<scriptb ></scriptb>"
        "<scriptb a=\"\"></scriptb>"
        "<scriptc a=\"\"b=\"\"></scriptc>"
        "<scriptd a=\"\" b=\"\"></scriptd>"
        "<scriptg a=\">\" b=\"\"></scriptg>"
        "<scripth a=\">\" b=\""
        "\"></scripth>"
        "<scripti a=\"\" b=\""
        "\"></scripti>"
        "\n"
        "<scripte>"
        "    // </scripte>"
        "</scripte>"
        "\n"
        "<scriptf>"
        "    /*"
        "    </scriptf>"
        "    */"
        "</scriptf>"
        "\n"
        "<br/>"
        "<br />"
        "<img src=\"image.jpg\" alt=\"An image>\" />"
        "<img src=\"image.jpg\" alt=\"An image/>\" />"
        "<img src=\"image.jpg\"alt=\"An image/>\" />"
        "\n"
        "<!-- comment -->", {
            "script",
            "scripta",
            "scriptb",
            "scriptc",
            "scriptd",
            "scripte",
            "scriptf",
            "scriptg",
            "scripth",
            "scripti"
        }, {"br", "img"}), "\n\n\n\n<br/><br /><img src=\"image.jpg\" alt=\"An image>\" /><img src=\"image.jpg\" alt=\"An image/>\" /><img src=\"image.jpg\"alt=\"An image/>\" />\n<!-- comment -->");

    UNIT_TEST_EQ(tvnj::sanitizeSVG("<UL><li><A HREF=//google.com>click</UL>"), "");
    UNIT_TEST_EQ(tvnj::sanitizeSVG("<TABLE><tr><td>HELLO</tr></TABL>"), "<TABLE></TABL>");
    UNIT_TEST_EQ(tvnj::sanitizeSVG("<p>abc<iframe//src=jAva&Tab;script:alert(3)>def</p>"), "");
    UNIT_TEST_EQ(tvnj::sanitizeSVG("<svg><g/onload=alert(2)//<p>"), "<svg><g/onload=alert(2)//<p>");
    UNIT_TEST_EQ(tvnj::sanitizeSVG("<img src=\"x\" onerror=\"alert(1)//\">"), "<img src=\"x\" onerror=\"alert(1)//\">"); // no closing tag
    UNIT_TEST_EQ(tvnj::sanitizeSVG("<img src=\"x\" onerror=\"alert(1)//\"></img>"), "");
    UNIT_TEST_EQ(tvnj::sanitizeSVG("<img src=\"x\"onerror=\"alert(1)/\"/>"), "");
    UNIT_TEST_EQ(tvnj::sanitizeSVG("<img src=x onerror=alert(1)//>"), "<img src=x onerror=alert(1)//>"); // quotes only attributes
    // quotes optional attributes
    UNIT_TEST_EQ(tvnj::sanitizeMarkupLanguage("<img src=x onerror=alert(1)/>", {
        "animate",
        "color-profile",
        "cursor",
        "discard",
        "font-face",
        "font-face-format",
        "font-face-name",
        "font-face-src",
        "font-face-uri",
        "foreignobject",
        "hatch",
        "hatchpath",
        "mesh",
        "meshgradient",
        "meshpatch",
        "meshrow",
        "missing-glyph",
        "script",
        "set",
        "solidcolor",
        "unknown",
        "use"
    }, {
        "a",
        "animate",
        "animateMotion",
        "animateTransform",
        "circle",
        "clipPath",
        "defs",
        "desc",
        "discard",
        "ellipse",
        "feBlend",
        "feColorMatrix",
        "feComponentTransfer",
        "feComposite",
        "feConvolveMatrix",
        "feDiffuseLighting",
        "feDisplacementMap",
        "feDistantLight",
        "feDropShadow",
        "feFlood",
        "feFuncA",
        "feFuncB",
        "feFuncG",
        "feFuncR",
        "feGaussianBlur",
        "feImage",
        "feMerge",
        "feMergeNode",
        "feMorphology",
        "feOffset",
        "fePointLight",
        "feSpecularLighting",
        "feSpotLight",
        "feTile",
        "feTurbulence",
        "filter",
        "foreignObject",
        "g",
        "image",
        "line",
        "linearGradient",
        "marker",
        "mask",
        "metadata",
        "mpath",
        "path",
        "pattern",
        "polygon",
        "polyline",
        "radialGradient",
        "rect",
        "script",
        "set",
        "stop",
        "style",
        "svg",
        "switch",
        "symbol",
        "text",
        "textPath",
        "title",
        "tspan",
        "use",
        "view"
    }, false), "");

    tvnj::Trie trie;

    UNIT_TEST_EQ(trie.search(""), false);

    trie.insert("apple");
    trie.insert("app");
    trie.insert("bat");

    UNIT_TEST_EQ(trie.search("apple"), true);
    trie.remove("apple");
    UNIT_TEST_EQ(trie.search("apple"), false);
    UNIT_TEST_EQ(trie.search("app"), true);
    trie.remove("app");
    UNIT_TEST_EQ(trie.search("app"), false);
    UNIT_TEST_EQ(trie.search("bat"), true);

    trie.insert("apple");
    trie.insert("app");
    UNIT_TEST_EQ(trie.startsWith("ba"), true);
    UNIT_TEST_EQ(trie.startsWith("a"), true);
    UNIT_TEST_EQ(trie.startsWith("ap"), true);
    UNIT_TEST_EQ(trie.startsWith("appl"), true);

    trie.remove("apple");
    trie.remove("app");
    UNIT_TEST_EQ(trie.startsWith("ba"), true);
    UNIT_TEST_EQ(trie.startsWith("a"), false);
    UNIT_TEST_EQ(trie.startsWith("ap"), false);
    UNIT_TEST_EQ(trie.startsWith("appl"), false);

    UNIT_TEST_EQ(trie.search(""), false);
    trie.remove("bat");
    UNIT_TEST_EQ(trie.search(""), false);

    trie.insert("");
    UNIT_TEST_EQ(trie.search(""), true);
    trie.remove("");
    UNIT_TEST_EQ(trie.search(""), false);

    tvnj::Trie* heapTrie = new tvnj::Trie();
    delete heapTrie;

    tvnj::AhoCorasick ahoCorasick;

    UNIT_TEST_EQ(vectorPairToString(ahoCorasick.search("")), "");
    UNIT_TEST_EQ(vectorPairToString(ahoCorasick.search("apple")), "");
    std::vector<std::string> wordList = {"apple", "app", "bat"};
    ahoCorasick.build(wordList);

    UNIT_TEST_EQ(vectorPairToString(ahoCorasick.search("apple")), "(0 3), (0 5)");
    UNIT_TEST_EQ(vectorPairToString(ahoCorasick.search("app")), "(0 3)");
    UNIT_TEST_EQ(vectorPairToString(ahoCorasick.search("bat")), "(0 3)");
    UNIT_TEST_EQ(vectorPairToString(ahoCorasick.search("batapple")), "(0 3), (3 3), (3 5)");

    ahoCorasick.remove("apple");
    UNIT_TEST_EQ(vectorPairToString(ahoCorasick.search("apple")), "(0 3)");
    UNIT_TEST_EQ(vectorPairToString(ahoCorasick.search("app")), "(0 3)");
    ahoCorasick.remove("app");
    UNIT_TEST_EQ(vectorPairToString(ahoCorasick.search("app")), "");
    UNIT_TEST_EQ(vectorPairToString(ahoCorasick.search("bat")), "(0 3)");

    ahoCorasick.insert("apple");
    ahoCorasick.insert("app");
    UNIT_TEST_EQ(vectorPairToString(ahoCorasick.search("apple")), "(0 3), (0 5)");
    UNIT_TEST_EQ(vectorPairToString(ahoCorasick.search("app")), "(0 3)");

    UNIT_TEST_EQ(vectorPairToString(ahoCorasick.search("")), "");
    ahoCorasick.remove("bat");
    UNIT_TEST_EQ(vectorPairToString(ahoCorasick.search("")), "");

    ahoCorasick.insert("");
    UNIT_TEST_EQ(vectorPairToString(ahoCorasick.search("")), "(0 0)");
    ahoCorasick.remove("");
    UNIT_TEST_EQ(vectorPairToString(ahoCorasick.search("")), "");

    ahoCorasick.insert("i");
    ahoCorasick.insert("in");
    ahoCorasick.insert("tin");
    ahoCorasick.insert("sting");
    UNIT_TEST_EQ(vectorPairToString(ahoCorasick.search("stings")), "(2 1), (1 3), (2 2), (0 5)");

    tvnj::AhoCorasick* heapAhoCorasick = new tvnj::AhoCorasick();
    delete heapAhoCorasick;

    tvnj::AhoCorasickFilter ahoCorasickFilter;

    UNIT_TEST_EQ(vectorPairToString(ahoCorasickFilter.search("")), "");
    UNIT_TEST_EQ(vectorPairToString(ahoCorasickFilter.search("apple")), "");
    ahoCorasickFilter.build(wordList);

    UNIT_TEST_EQ(vectorPairToString(ahoCorasickFilter.search("apple")), "(0 3), (0 5)");
    UNIT_TEST_EQ(vectorPairToString(ahoCorasickFilter.search("app")), "(0 3)");
    UNIT_TEST_EQ(vectorPairToString(ahoCorasickFilter.search("bat")), "(0 3)");
    UNIT_TEST_EQ(vectorPairToString(ahoCorasickFilter.search("batapple")), "(0 3), (3 3), (3 5)");

    ahoCorasickFilter.remove("apple");
    UNIT_TEST_EQ(vectorPairToString(ahoCorasickFilter.search("apple")), "(0 3)");
    UNIT_TEST_EQ(vectorPairToString(ahoCorasickFilter.search("app")), "(0 3)");
    ahoCorasickFilter.remove("app");
    UNIT_TEST_EQ(vectorPairToString(ahoCorasickFilter.search("app")), "");
    UNIT_TEST_EQ(vectorPairToString(ahoCorasickFilter.search("bat")), "(0 3)");

    ahoCorasickFilter.insert("apple");
    ahoCorasickFilter.insert("app");
    UNIT_TEST_EQ(vectorPairToString(ahoCorasickFilter.search("apple")), "(0 3), (0 5)");
    UNIT_TEST_EQ(vectorPairToString(ahoCorasickFilter.search("app")), "(0 3)");

    UNIT_TEST_EQ(vectorPairToString(ahoCorasickFilter.search("")), "");
    ahoCorasickFilter.remove("bat");
    UNIT_TEST_EQ(vectorPairToString(ahoCorasickFilter.search("")), "");

    ahoCorasickFilter.insert("");
    UNIT_TEST_EQ(vectorPairToString(ahoCorasickFilter.search("")), "(0 0)");
    ahoCorasickFilter.remove("");
    UNIT_TEST_EQ(vectorPairToString(ahoCorasickFilter.search("")), "");

    //-----

    UNIT_TEST_EQ(ahoCorasickFilter.filter("apple"), "*****");
    UNIT_TEST_EQ(ahoCorasickFilter.filter("app"), "***");
    UNIT_TEST_EQ(ahoCorasickFilter.filter("bat"), "bat");
    UNIT_TEST_EQ(ahoCorasickFilter.filter("batapple"), "bat*****");
    UNIT_TEST_EQ(ahoCorasickFilter.filter(""), "");

    ahoCorasickFilter.insert("bat");
    UNIT_TEST_EQ(ahoCorasickFilter.filter("bat"), "***");
    UNIT_TEST_EQ(ahoCorasickFilter.filter("batapple"), "********");
    UNIT_TEST_EQ(ahoCorasickFilter.filter("bataapple"), "***a*****");
    UNIT_TEST_EQ(ahoCorasickFilter.filter("batapapple"), "***ap*****");

    ahoCorasickFilter.insert("");
    UNIT_TEST_EQ(ahoCorasickFilter.filter("apple"), "*****");
    UNIT_TEST_EQ(ahoCorasickFilter.filter("app"), "***");
    UNIT_TEST_EQ(ahoCorasickFilter.filter("bat"), "***");
    UNIT_TEST_EQ(ahoCorasickFilter.filter("batapple"), "********");
    UNIT_TEST_EQ(ahoCorasickFilter.filter(""), "");

    //-----

    UNIT_TEST_EQ(ahoCorasickFilter.filterAndIgnoreChars("apple", "*", std::unordered_set<char>()), "*****");
    UNIT_TEST_EQ(ahoCorasickFilter.filterAndIgnoreChars("app", "*", std::unordered_set<char>()), "***");
    UNIT_TEST_EQ(ahoCorasickFilter.filterAndIgnoreChars("", "*", std::unordered_set<char>()), "");
    UNIT_TEST_EQ(ahoCorasickFilter.filterAndIgnoreChars("bat", "*", std::unordered_set<char>()), "***");
    UNIT_TEST_EQ(ahoCorasickFilter.filterAndIgnoreChars("batapple", "*", std::unordered_set<char>()), "********");
    UNIT_TEST_EQ(ahoCorasickFilter.filterAndIgnoreChars("bataapple", "*", std::unordered_set<char>()), "***a*****");
    UNIT_TEST_EQ(ahoCorasickFilter.filterAndIgnoreChars("batapapple", "*", std::unordered_set<char>()), "***ap*****");

    ahoCorasickFilter = tvnj::AhoCorasickFilter();
    wordList = {"apple", "app", "bat", "apapple"};
    ahoCorasickFilter.build(wordList);
    UNIT_TEST_EQ(ahoCorasickFilter.filterAndIgnoreChars("batapapple", "*", std::unordered_set<char>()), "**********");
    UNIT_TEST_EQ(ahoCorasickFilter.filterAndIgnoreChars("bataapapple", "*", std::unordered_set<char>()), "***a*******");

    ahoCorasickFilter = tvnj::AhoCorasickFilter();
    wordList = {"apple", "app", "bat", "apap"};
    ahoCorasickFilter.build(wordList);

    UNIT_TEST_EQ(ahoCorasickFilter.filterAndIgnoreChars("batapapple", "*", std::unordered_set<char>()), "**********");
    UNIT_TEST_EQ(ahoCorasickFilter.filterAndIgnoreChars("bataapapple", "*", std::unordered_set<char>()), "***a*******");

    ahoCorasickFilter = tvnj::AhoCorasickFilter();
    ahoCorasickFilter.insert("135"); // used to not work with class reinitialization
    UNIT_TEST_EQ(ahoCorasickFilter.filterAndIgnoreChars("123456", "*", std::unordered_set<char>{'2', '4', '6'}), "*2*4*6");

    ahoCorasickFilter = tvnj::AhoCorasickFilter();
    wordList = {"135"};
    ahoCorasickFilter.build(wordList); // works with class reinitialization even before the fix
    UNIT_TEST_EQ(ahoCorasickFilter.filterAndIgnoreChars("123456", "*", std::unordered_set<char>{'2', '4', '6'}), "*2*4*6");
}

#endif
