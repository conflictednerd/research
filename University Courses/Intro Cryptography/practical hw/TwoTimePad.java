import java.util.ArrayList;
import java.util.List;

public class TwoTimePad {

    public static void main(String[] args) {
        //key[i] contains a bit string of length 8 that will encrypt ith char of ciphers.
        String[] key = new String[1000];
        List<String> ciphers = new ArrayList<>();
        init(ciphers);
        String targetCipher = "32510ba9babebbbefd001547a810e67149caee11d945cd7fc81 a05e9f85aac650e9052ba6a8cd8257bf14d13e6f0a803b54fde 9e77472dbff89d71b57bddef121336cb85ccb8f3315f4b52e30 1d16e9f52f904".replaceAll("\\s", "");
        for (int i = 0; i < ciphers.size(); i++) {
            ciphers.set(i, hexToBin(ciphers.get(i)));
        }
        targetCipher = hexToBin(targetCipher);

        for (int i = 0; i < ciphers.size(); i++) {
            int[] counter = new int[ciphers.get(i).length() / 8];
            for (int j = 0; j < ciphers.size(); j++) {
                if (i == j) continue;
                String x = xor(ciphers.get(i), ciphers.get(j));
                for (int k = 0; k < Math.min(ciphers.get(i).length(), ciphers.get(j).length()) / 8; k++) {
                    //kth character of one of the strings is a space(we don't know which one)
                    if (x.charAt(8 * k + 1) == '1') {
                        counter[k]++;
                    }
                }
            }
            for (int j = 0; j < ciphers.get(i).length() / 8; j++) {
                //it is unlikely that jth char of ith message is not a space because otherwise counter[j]>6 other messages
                //must have a space as their jth char.
                if (counter[j] > 6) {
                    //jth char of ith message was a space
                    key[j] = xor("00100000", ciphers.get(i).substring(8 * j, 8 * j + 8));
                }
            }
        }

        StringBuilder ans = new StringBuilder();
        for (int i = 0; i < targetCipher.length() / 8; i++) {
            if (key[i] == null) {
                ans.append("-");
            } else {
                ans.append((char) (Integer.parseInt(xor(key[i], targetCipher.substring(8 * i, 8 * i + 8)), 2)));
            }
        }
        System.out.println(ans.toString());
        //The secret message appears to be: "The secret message is: When using a stream cipher, never use the key more than once".
        //We check this by generating the key using our guess and decrypting all other ciphertexts.
        String targetMessage = "The secret message is: When using a stream cipher, never use the key more than once";
        String keyy = xor(targetCipher, hexToBin(stringToHex(targetMessage)));
        for (String c : ciphers) {
            StringBuilder anss = new StringBuilder();
            for (int i = 0; i < keyy.length() / 8; i++) {
                anss.append((char) (Integer.parseInt(xor(keyy.substring(8 * i, 8 * i + 8), c.substring(8 * i, 8 * i + 8)), 2)));

            }
            System.out.println(anss.toString());
        }
    }

    private static void init(List<String> ciphers) {
        ciphers.add("315c4eeaa8b5f8aaf9174145bf43e1784b8fa00dc71d885a804e5ee9fa40b16349c146fb778cdf2d3aff021dfff5b403b510d0d0455468aeb98622b137dae857553ccd8883a7bc37520e06e515d22c954eba5025b8cc57ee59418ce7dc6bc41556bdb36bbca3e8774301fbcaa3b83b220809560987815f65286764703de0f3d524400a19b159610b11ef3e");
        ciphers.add("234c02ecbbfbafa3ed18510abd11fa724fcda2018a1a8342cf0 64bbde548b12b07df44ba7191d9606ef4081ffde5ad46a5069d 9f7f543bedb9c861bf29c7e205132eda9382b0bc2c5c4b45f91 9cf3a9f1cb74151f6d551f4480c82b2cb24cc5b028aa76eb7b4 ab24171ab3cdadb8356f ".replaceAll("\\s", ""));
        ciphers.add("32510ba9a7b2bba9b8005d43a304b5714cc0bb0c8a34884dd91 304b8ad40b62b07df44ba6e9d8a2368e51d04e0e7b207b70b9b 8261112bacb6c866a232dfe257527dc29398f5f3251a0d47e50 3c66e935de81230b59b7afb5f41afa8d661cb ".replaceAll("\\s", ""));
        ciphers.add("32510ba9aab2a8a4fd06414fb517b5605cc0aa0dc91a8908c20 64ba8ad5ea06a029056f47a8ad3306ef5021eafe1ac01a81197 847a5c68a1b78769a37bc8f4575432c198ccb4ef63590256e30 5cd3a9544ee4160ead45aef520489e7da7d835402bca670bda8 eb775200b8dabbba246b130f040d8ec6447e2c767f3d30ed81e a2e4c1404e1315a1010e7229be6636aaa".replaceAll("\\s", ""));
        ciphers.add("3f561ba9adb4b6ebec54424ba317b564418fac0dd35f8c08d31 a1fe9e24fe56808c213f17c81d9607cee021dafe1e001b21ade 877a5e68bea88d61b93ac5ee0d562e8e9582f5ef375f0a4ae20 ed86e935de81230b59b73fb4302cd95d770c65b40aaa065f2a5 e33a5a0bb5dcaba43722130f042f8ec85b7c2070 ".replaceAll("\\s", ""));
        ciphers.add("32510bfbacfbb9befd54415da243e1695ecabd58c519cd4bd20 61bbde24eb76a19d84aba34d8de287be84d07e7e9a30ee71497 9c7e1123a8bd9822a33ecaf512472e8e8f8db3f9635c1949e64 0c621854eba0d79eccf52ff111284b4cc61d11902aebc66f2b2 e436434eacc0aba938220b084800c2ca4e693522643573b2c4c e35050b0cf774201f0fe52ac9f26d71b6cf61a711cc229f77ac e7aa88a2f19983122b11be87a59c355d25f8e4 ".replaceAll("\\s", ""));
        ciphers.add("32510bfbacfbb9befd54415da243e1695ecabd58c519cd4bd90 f1fa6ea5ba47b01c909ba7696cf606ef40c04afe1ac0aa8148d d066592ded9f8774b529c7ea125d298e8883f5e9305f4b44f91 5cb2bd05af51373fd9b4af511039fa2d96f83414aaaf261bda2 e97b170fb5cce2a53e675c154c0d9681596934777e2275b381c e2e40582afe67650b13e72287ff2270abcf73bb028932836fbd ecfecee0a3b894473c1bbeb6b4913a536ce4f9b13f1efff71ea 313c8661dd9a4ce ".replaceAll("\\s", ""));
        ciphers.add("315c4eeaa8b5f8bffd11155ea506b56041c6a00c8a08854dd21 a4bbde54ce56801d943ba708b8a3574f40c00fff9e00fa1439f d0654327a3bfc860b92f89ee04132ecb9298f5fd2d5e4b45e40 ecc3b9d59e9417df7c95bba410e9aa2ca24c5474da2f276baa3 ac325918b2daada43d6712150441c2e04f6565517f317da9d3 ".replaceAll("\\s", ""));
        ciphers.add("271946f9bbb2aeadec111841a81abc300ecaa01bd8069d5cc91 005e9fe4aad6e04d513e96d99de2569bc5e50eeeca709b50a8a 987f4264edb6896fb537d0a716132ddc938fb0f836480e06ed0 fcd6e9759f40462f9cf57f4564186a2c1778f1543efa270bda5 e933421cbe88a4a52222190f471e9bd15f652b653b7071aec59 a2705081ffe72651d08f822c9ed6d76e48b63ab15d0208573a7 eef027".replaceAll("\\s", ""));
        ciphers.add("466d06ece998b7a2fb1d464fed2ced7641ddaa3cc31c9941cf1 10abbf409ed39598005b3399ccfafb61d0315fca0a314be138a 9f32503bedac8067f03adbf3575c3b8edc9ba7f537530541ab0 f9f3cd04ff50d66f1d559ba520e89a2cb2a83 ".replaceAll("\\s", ""));
        ciphers.add("32510ba9babebbbefd001547a810e67149caee11d945cd7fc81 a05e9f85aac650e9052ba6a8cd8257bf14d13e6f0a803b54fde 9e77472dbff89d71b57bddef121336cb85ccb8f3315f4b52e30 1d16e9f52f904".replaceAll("\\s", ""));
    }

    private static String stringToHex(String s) {
        StringBuilder res = new StringBuilder();
        for (char c : s.toCharArray()) {
            res.append(Integer.toHexString(c));
        }
        return res.toString();
    }

    private static String xor(String s, String t) {
        StringBuilder res = new StringBuilder();
        for (int i = 0; i < Math.min(s.length(), t.length()); i++) {
            if (s.charAt(i) == t.charAt(i)) {
                res.append("0");
            } else {
                res.append("1");
            }
        }
        return res.toString();
    }

    private static String hexToBin(String s) {
        StringBuilder ans = new StringBuilder();
        String temp;
        for (int i = 0; i < s.length(); i += 2) {
            temp = Integer.toBinaryString(Integer.parseInt(s.substring(i, i + 2), 16));
            while (temp.length() < 8) {
                temp = "0" + temp;
            }
            ans.append(temp);
        }
        return ans.toString();
    }
}