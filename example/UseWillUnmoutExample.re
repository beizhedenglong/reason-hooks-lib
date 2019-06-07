[@react.component]
let make = () => {
  Lifecycle.(useWillUnmount(() => Js.log("willUnmount")));
  React.null;
};