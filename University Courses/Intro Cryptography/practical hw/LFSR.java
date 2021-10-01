public class LFSR {
    //a is LFSR's transition matrix.
    static int[][] a = new int[51][51];
    //b is the system of linear equations we wish to solve
    static int[][] b = new int[10000][52];
    static int bRows = 0;

    static int[] decCipher = new int[10000];
    static int decCipherLen = 0;

    static int[] decText = new int[10000];
    static String plainText = "";

    static int[] key = new int[51];

    public static void main(String[] args) {
        String cipher = "6d2a42943f64e701286b8d0cb90f6855673b48eb5b8e056742 cb29007c1dcf1220a0ddc6c33096e26cf9d1fa17812c5e7245 6676c0225b4773c70963431d224d616779ca6427f1203e783c 896f82be39f15917a21f41b03d74abe256e8c2474cae0b55df 296647b070724466d0ac61078b691975359bd19ce1bbb3060c e5e54c52f83325d32933a57581ec189c4b12f8fc9459ad3f51 7ee171204164165922340a9f875bbf7d16a618ffb37bfee8ab 4cae305aa76256dde144b92083ba3858af5a8ae2b5a75bd30a 053b9287d876ac0721e543975f8cc430b8327351ca7c6ac859 2b7f7463b062256316c0bf3de55d989527cd0f7e1007b482a1 599f1167ab23d2e8db7be9763f5a956519e6256b4e196a31cb 288da335e69496cb3fa5beb55d899d6c5b142c7169c35d1504 04481710218dd1da824927f8514e5eddc95d1efd22d2ef9b87 8af2596d00077899eb4cfdaeb8e9bbee0c273243142e3ef6a3 f43a138d2d".replaceAll("\\s", "");
        for (int i = 0; 2 * i < cipher.length(); i++) {
            decCipher[i] = Integer.parseInt(cipher.substring(2 * i, 2 * i + 2), 16);
        }
        assert ((cipher.length() % 2) == 0);
        decCipherLen = cipher.length() / 2;

        //initialize a
        for (int i = 0; i < 51; i++) {
            for (int j = 0; j < 51; j++) {
                a[i][j] = 0;
            }
        }
        for (int i = 0; i < 50; i++) {
            a[i][i + 1] = 1;
        }
        a[50][0] = 1;
        a[50][9] = 1;


        //calculate b
        for (int i = 0; i < decCipherLen; i++) {
            bRows++;
            int[] temp = power(a, 8 * i);
            for (int j = 0; j < 51; j++) {
                b[i][j] = temp[j];
            }

            //8*i th bit of lfsr's output is 1.
            if (decCipher[i] >= 128) {
                b[i][51] = 1;
            } else {
                b[i][51] = 0;
            }
        }

//        printB();

        //solve b to obtain s0, s1, ..., s50
        for (int i = 0; i < 51; i++) {
            //replace rows such that b[i][i] = 1.
            for (int j = i; j < bRows; j++) {
                if (b[j][i] == 1) {
                    replaceRows(i, j);
                    break;
                }
            }
            for (int j = 0; j < bRows; j++) {
                if(i != j && b[j][i] == 1){
                    addRows(i, j);
                }
            }
        }

//        printB();

        System.out.println("LFSR's initial value is: ");
        //Now, let's find the initial state of LFSR
        for(int i = 0; i<51; i++){
            key[i] = b[i][51];
            System.out.print(key[i]);
        }
        System.out.println();

        for(int i = 0; i<decCipherLen; i++){
            int p = 128;
            int c = 0;
            for(int j = 0; j<8;j++){
                c += (p*click());
                p/=2;
            }
            decText[i] = c^decCipher[i];
            plainText += (char)decText[i];
        }

        System.out.println("Secret message is: ");
        System.out.println(plainText);

    }

    private static int click() {
        int out = key[0], in = key[0]^key[9];
        for(int i = 0; i<50; i++){
            key[i] = key[i+1];
        }
        key[50] = in;
        return out;
    }

    private static void printMatrix(int[][] matrix) {
        for(int i = 0; i<51; i++){
            for(int j = 0; j<51; j++){
                System.out.print(matrix[i][j] + " ");
            }
            System.out.println();
        }
    }

    private static void printB() {
        for(int i = 0; i<bRows; i++){
            for(int j = 0; j<52; j++){
                System.out.print(b[i][j] + " ");
            }
            System.out.println();
        }
    }

    private static int[][] ppower(int[][] matrix, int pow){
        if(pow == 0){
            int[][] P = new int[51][51];
            //P is initially identity matrix
            for (int i = 0; i < 51; i++) {
                P[i][i] = 1;
            }
            return P;
        }
        if(pow %2 == 0){
            return ppower(mult(matrix, matrix), pow/2);
        }
        return mult(matrix, ppower(matrix, pow-1));
    }

    //returns the first row of matrix^pow
    private static int[] power(int[][] matrix, int pow) {
        int[] ans = new int[51];
        int[][] P = ppower(matrix, pow);
        for (int i = 0; i < 51; i++) {
            ans[i] = P[0][i];
        }
        return ans;
    }

    private static int[][] mult(int[][] m, int[][] mm) {
        int[][] ans = new int[51][51];
        for (int i = 0; i < 51; i++) {
            for (int j = 0; j < 51; j++) {
                for (int k = 0; k < 51; k++) {
                    //xor with their and
                    ans[i][j] ^= (m[i][k] & mm[k][j]);
                }
            }
        }
        return ans;
    }

    //replaces rows m, n of b
    private static void replaceRows(int m, int n) {
        if (m == n) return;
        int temp = 0;
        for (int i = 0; i < 52; i++) {
            temp = b[m][i];
            b[m][i] = b[n][i];
            b[n][i] = temp;
        }
    }

    //adds row m of b to row n of b
    private static void addRows(int m, int n) {
        assert m != n;
        for (int i = 0; i < 52; i++) {
            b[n][i] ^= b[m][i];
            assert b[n][i] < 2;
        }
    }

}
