package net.joker.utils;

/**
 * @author serafith
 * Enum couleur console
 *
 */
public enum ColorConsole {

	RESET("\u001B[0m"),
	RED("\u001B[31m"),
	GREEN("\u001B[32m"),
	YELLOW("\u001B[33m");
	
	private String code;
	
	ColorConsole(String code) {
		this.code = code;
	}
	
	public String getColor() {
		return this.code;
	}
}
