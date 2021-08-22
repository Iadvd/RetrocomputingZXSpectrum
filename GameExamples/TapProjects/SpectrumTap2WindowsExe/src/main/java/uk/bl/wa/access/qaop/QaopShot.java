package uk.bl.wa.access.qaop;

import java.awt.Color;
import java.awt.Frame;
import java.awt.Graphics;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.util.Hashtable;

import javax.imageio.ImageIO;

/**
 *
 */

/**
 * Wrapping up Qaop to generate a screenshot.
 *
 * @author Andrew Jackson <Andrew.Jackson@bl.uk>
 *
 */
public class QaopShot {

    /**
     * Takes a screenshot of the emulator, after waiting a short while.
     *
     * Can be passed a URL, but is a little slow, so makes timing the shot more brittle.
     *
     * @param args
     * @throws IOException
     */
    public static void main(String[] args) throws IOException {
        // Get filename:
        String file = args[0];

        // Take shot and save as PNG
        takeScreenshot(file, file + ".png", 3);

        // Close:
        System.exit(0);
    }

    /**
     * Take a screenshot and save it as a PNG file.
     *
     * @param input
     * @param output
     * @param delay
     * @throws IOException
     */
    public static void takeScreenshot(String input, String output, int delay) throws IOException {
        ImageIO.write(takeScreenshot(input, delay), "png", new File(output));
    }

    /**
     *
     * @param input
     * @param outputstream
     * @param delay
     * @throws IOException
     */
    public static void takeScreenshot(String input, OutputStream outputstream, int delay) throws IOException {
        ImageIO.write(takeScreenshot(input, delay), "png", outputstream);
    }

    /**
     *
     * @param inputstream
     * @param extension e.g. "tap" to indicated this is a TAP file.
     * @param outputstream
     * @param delay
     * @throws IOException
     */
    public static void takeScreenshot(InputStream inputstream, String extension, OutputStream outputstream, int delay) throws IOException {
        File input = File.createTempFile("spectrum-tape", "." + extension);
        ImageIO.write(takeScreenshot(input.getCanonicalPath(), delay), "png", outputstream);
    }

    /**
     * Fire up a spectrum emulator, wait, and then take a screenshot.
     *
     * @param input
     * @param delay in seconds
     * @return
     */
    public static BufferedImage takeScreenshot(String input, int delay) {
        Frame f = new Frame("Qaop");
        Qaop q = new Qaop();

        Hashtable<String, String> p = new Hashtable<String, String>();
        p.put("load", input);
        // Disable audio:
        p.put("ay", "0");

        f.setBackground(new Color(0x222222));
        f.add(q);
        f.addWindowListener(q);
        f.addKeyListener(q);
        f.pack();

        Qaop.param = p;
        q.init();
        f.setVisible(true);

        // Wait for three seconds:
        try {
            Thread.sleep(1000 * 3);
        } catch (InterruptedException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }

        // Save out screenshot:
        int width = q.getWidth();
        int height = q.getHeight();

        BufferedImage bi = new BufferedImage(width, height, BufferedImage.TYPE_INT_RGB);
        Graphics big = bi.getGraphics();
        q.paint(big);

        // Shutdown:
        f.setVisible(false);
        f.dispose();

        return bi;
    }

}
