[@react.component]
let make = (~counter) => {
  Lifecycle.(
    useDidUpdate(
      () => {
        Js.log("did update");
        None;
      },
      [|counter|],
    )
  );
  React.null;
};