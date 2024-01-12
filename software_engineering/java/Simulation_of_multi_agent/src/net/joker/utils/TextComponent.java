package net.joker.utils;

import java.util.Properties;

/**
 * @author serafith
 *	Ecrire en couleur dans la console
 */
public class TextComponent {
	
	private String text;
	private ColorConsole color = null;

	public TextComponent(ColorConsole color, String text) {
		this.text = text;
		this.color = color;
	}
	
	public TextComponent(String text) {
		this.text = text;
	}
	
	public String getMessage() {
		StringBuilder b = new StringBuilder();
		if(color != null) {
			b.append(color.getColor());
			
		}
		b.append(text);
		ColorConsole color = ColorConsole.RESET;
		b.append(color.getColor());
		b.append(System.getProperty("line.separator"));
		return b.toString();
	}
}
