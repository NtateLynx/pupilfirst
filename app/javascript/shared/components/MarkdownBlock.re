[@bs.config {jsx: 3}];
[%bs.raw {|require("./MarkdownBlock.css")|}];

let str = React.string;

let randomId = () => {
  let randomComponent =
    Js.Math.random() |> Js.Float.toString |> Js.String.substr(~from=2);
  "markdown-block-" ++ randomComponent;
};

let profileClasses = (profile: Markdown.profile) =>
  switch (profile) {
  | Comment => "markdown-block__comment "
  | QuestionAndAnswer => "markdown-block__questions-and-answer "
  | Permissive => "markdown-block__permissive "
  };

let markdownBlockClasses = (profile, className) => {
  let defaultClasses = "markdown-block " ++ profileClasses(profile);
  switch (className) {
  | Some(className) => defaultClasses ++ className
  | None => defaultClasses
  };
};

[@react.component]
let make = (~markdown, ~className=?, ~profile) => {
  let id = randomId();

  React.useEffect1(
    () => {
      PrismJs.highlightAllUnder(id);
      None;
    },
    [|markdown|],
  );

  <div
    className={markdownBlockClasses(profile, className)}
    id
    dangerouslySetInnerHTML={"__html": markdown |> Markdown.parse(profile)}
  />;
};
