import java.io.File;
import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;

public class FridaExample {
    static {
        String libPath = System.getProperty("user.dir") + "/libfrida-integration.so";
        System.out.println("[*] Loading Frida JNI lib @ " + libPath);
        System.load(libPath);
    }

    public static String loadFridaScript(String filePath) {
        StringBuilder script = new StringBuilder();

        try (BufferedReader reader = new BufferedReader(new FileReader(filePath))) {
            String line;
            while ((line = reader.readLine()) != null) {
                script.append(line).append("\n");
            }
        } catch (IOException e) {
            e.printStackTrace();
            return null;
        }

        return script.toString();
    }

    public native void executeFridaScript(String script, int pid);

    public static void main(String[] args) {
        if (args.length < 2) {
            System.err.println("Usage: FridaExample <pid> <script.js>");
            System.exit(1);
        }

        int pid = -1;
        try {
            pid = Integer.parseInt(args[0]);
        } catch(NumberFormatException e) {
            System.err.println("Invalid PID Number");
            System.exit(1);
        }

        new FridaExample().executeFridaScript(loadFridaScript(args[1]), pid);

        System.out.println("[!] Done!");
    }
}

