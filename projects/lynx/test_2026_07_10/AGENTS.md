# AGENTS.md

You are an expert in JavaScript, Rspeedy, and Lynx application development. You write maintainable, performant, and accessible code.

## Read in Advance

Read docs below in advance to help you understand the library or frameworks this project depends on.

- Lynx: [llms.txt](https://lynxjs.org/next/llms.txt), **REQUIRED**.
  While dealing with a Lynx task, an agent **MUST** read this doc because it is an entry point of all available docs about Lynx.

## Commands

- `npm run dev` - Start the dev server

- `npm run build` - Build the app for production

- `npm run preview` - Preview the production build locally

- `npm exec rspeedy inspect` - Inspect the Rspeedy config and Rspack config of the project.

## Related Docs

- Rsbuild: <https://rsbuild.rs/llms.txt>

- Rspack: <https://rspack.rs/llms.txt>

## MCP Servers

### Lynx Docs

For any questions or requirements regarding Lynx:

1. Use the "List Resources Tool" to list all Resources provided in MCP "lynx-docs".
2. First read MCP Resources "lynx-docs://llms.txt" (**REQUIRED**), this document is an ENTRYPOINT of all Lynx Docs.
3. After reading "lynx-docs://llms.txt", use the "Read MCP Resources Tool" to retrieve docs you need based on the user's questions or requirements, please read them proactively.
4. If available, prioritize obtaining Lynx-related information through MCP Resources tools over external web searches.

### Lynx DevTool

Use MCP "lynx-devtool" to control, operate, and preview Lynx pages (element inspection, console, screenshot, tap/drag interaction, etc.).

## Tools

### Biome

- Run `bun run lint` to lint your code
- Run `bun run format` to format your code
