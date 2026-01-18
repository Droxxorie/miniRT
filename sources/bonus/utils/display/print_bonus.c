/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 21:35:55 by eraad             #+#    #+#             */
/*   Updated: 2026/01/18 18:39:38 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

void	print_usage(void)
{
	printf(BOLD "\nUSAGE\n" RESET);
	printf("  ./miniRT_bonus <scene_file.rt> [flags]\n\n");
	printf(BOLD "ARGUMENTS\n" RESET);
	printf("  %-20s Path to the scene description file (.rt)\n\n",
		"<scene_file.rt>");
	printf(BOLD "OPTIONAL FLAGS\n" RESET);
	printf("  %-20s Render off-screen and save to 'output/' folder.\n",
		"--save");
	printf("  %-20s  Filename auto-generated (timestamp).\n\n", "");
	printf("  %-20s Render off-screen and save to specific path.\n",
		"--save <filename>");
	printf("  %-20s  (e.g., output.bmp)\n\n", "");
	printf("  %-20s Display this help message and exit.\n", "--help");
	printf("  %-20s Enable debug mode.\n", "--debug [options]");
	printf(BOLD "\nEXAMPLES\n" RESET);
	printf("  Launch interactive mode:\n");
	printf("    ./miniRT_bonus assets/scenes/example.rt\n\n");
	printf("  Render and save automatically:\n");
	printf("    ./miniRT_bonus assets/scenes/example.rt --save\n\n");
	printf("  Render and save as 'final.bmp':\n");
	printf("    ./miniRT_bonus assets/scenes/example.rt --save example.bmp\n");
	printf("  Render in debug mode:\n");
	printf("    ./miniRT_bonus assets/scenes/example.rt --debug AO\n");
	printf("    ./miniRT_bonus assets/scenes/example.rt --debug NORMAL\n");
	printf("\n");
}

void	print_controls(void)
{
	printf("\n%s╔═════════════════════════════════════════╗\n", Y);
	printf("║%s              miniRT CONTROLS            %s║\n", B_W, Y);
	printf("╚═════════════════════════════════════════╝\n");
	printf("╔═════════════════════════════════════════╗\n");
	printf("║%s  [ESC]         Exit Program             %s║\n", B_W, Y);
	printf("║%s  [ENTER]       Save Screenshot          %s║\n", B_W, Y);
	printf("║%s  [R]           Reset Selection          %s║\n", B_W, Y);
	printf("║%s  [SHIFT] + [R] Reset Scene              %s║\n", B_W, Y);
	printf("║%s                                         %s║\n", B_W, Y);
	printf("║%s  [TAB]         Switch ROT / TRANS Mode  %s║\n", B_W, Y);
	printf("║%s  [C] / [L]     Control Camera / Light   %s║\n", B_W, Y);
	printf("║%s  [SPACE]       Toggle Cam / Light       %s║\n", B_W, Y);
	printf("║%s  [R Click]     Select Object / Camera   %s║\n", B_W, Y);
	printf("║%s                                         %s║\n", B_W, Y);
	printf("║%s  [W / S]       Move Fwd / Back          %s║\n", B_W, Y);
	printf("║%s  [A / D]       Move Left / Right        %s║\n", B_W, Y);
	printf("║%s  [Q / E]       Move Up / Down           %s║\n", B_W, Y);
	printf("║%s                                         %s║\n", B_W, Y);
	printf("║%s  [Scroll ↑/↓]            Resize Height  %s║\n", B_W, Y);
	printf("║%s  [SHIFT] + [Scroll ↑/↓]  Resize Width   %s║\n", B_W, Y);
	printf("║%s  [CTRL] + [Scroll ↑/↓]   Resize Radius  %s║\n", B_W, Y);
	printf("╚═════════════════════════════════════════╝\n");
	printf(RESET "\n");
}
